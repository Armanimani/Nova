#include "Engine/Systems/Graphics/Platform/DirectX12/DX12GraphicContext.hpp"
#include "Engine/Systems/Graphics/Platform/DirectX12/DX12SwapChainFactory.hpp"
#include "Engine/Logging/ConsoleLogger.hpp"
#include <cassert>

namespace nova
{
	DX12GraphicContext::DX12GraphicContext([[maybe_unused]] const GraphicSettings& settings, void* window_handle)
		: handle{ static_cast<HWND>(window_handle) }
	{
		if (settings.is_triple_buffering_enabled)
			buffer_count = 3;
		else
			buffer_count = 2;
	}

	void DX12GraphicContext::initialize() noexcept
	{
		// TODO: add a custom compiling rule for debug mode
		device = std::make_unique<DX12Device>(true);
		
		rtv_descriptor_size = device->getRtvDescriptorSize();
		dsv_descriptor_size = device->getDsvDescriptorSize();
		cbv_srv_uav_descriptor_size = device->getCbvSrvUavDescriptorSize();
		
		createFences();
		createCommandObjects();
		createSwapChain();
		createRtvAndDsvDescriptorHeaps();
	}

	void DX12GraphicContext::createRtvAndDsvDescriptorHeaps() noexcept
	{
		rtv_descriptor_heap = device->createDescriptorHeap(D3D12_DESCRIPTOR_HEAP_TYPE_RTV, buffer_count);
		dsv_descriptor_heap = device->createDescriptorHeap(D3D12_DESCRIPTOR_HEAP_TYPE_DSV, buffer_count);

		// TODO: Move this to resize event
		CD3DX12_CPU_DESCRIPTOR_HANDLE rtv_handle(rtv_descriptor_heap->GetCPUDescriptorHandleForHeapStart());
		for (UInt32 i = 0; i != buffer_count; ++i)
		{
			back_buffer_list.emplace_back(nullptr);
			const auto result = swap_chain->GetBuffer(i, IID_PPV_ARGS(&back_buffer_list[i]));

			if (FAILED(result))
			{
				ConsoleLogger::logCritical(k_dx12_channel, "Unable to get the back buffer from swap chain for DirectX12");
			}

			device->getNative()->CreateRenderTargetView(back_buffer_list[i].Get(), nullptr, rtv_handle);
			rtv_handle.Offset(rtv_descriptor_size);
		}
	}

	void DX12GraphicContext::createCommandObjects() noexcept
	{
		graphic_command_queue = device->createCommandQueue(D3D12_COMMAND_LIST_TYPE_DIRECT, D3D12_COMMAND_QUEUE_PRIORITY_NORMAL);

		for (UInt32 i = 0; i != buffer_count; ++i)
			command_allocator_list.push_back(device->createCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT));

		graphic_command_list = device->createCommandList(D3D12_COMMAND_LIST_TYPE_DIRECT, command_allocator_list[0]);
	}

	void DX12GraphicContext::createSwapChain() noexcept
	{
		swap_chain = DX12SwapChainFactory::create(graphic_command_queue, handle, 0, 0, buffer_count);
	}

	void DX12GraphicContext::createFences() noexcept
	{
		for (UInt32 i = 0; i != buffer_count; ++i)
		{
			const auto fence = DX12Fence(device->getNative(), D3D12_FENCE_FLAG_NONE);
			fence_list.push_back(fence);
		}
	}

	D3D12_CPU_DESCRIPTOR_HANDLE DX12GraphicContext::getCurrentBackBufferViewHandle() const noexcept
	{
		return CD3DX12_CPU_DESCRIPTOR_HANDLE(
			rtv_descriptor_heap->GetCPUDescriptorHandleForHeapStart(),
			frame_index,
			rtv_descriptor_size);
	}
	
	D3D12_CPU_DESCRIPTOR_HANDLE DX12GraphicContext::getCurrentDepthStencilViewHandle() const noexcept
	{
		return dsv_descriptor_heap->GetCPUDescriptorHandleForHeapStart();
	}

	ID3D12Resource* DX12GraphicContext::getCurrentBackBuffer() const noexcept
	{
		return back_buffer_list[frame_index].Get();
	}

	void DX12GraphicContext::present() noexcept
	{
		updatePipeline();

		ID3D12CommandList* const command_list[] =
		{
			graphic_command_list.Get()
		};

		graphic_command_queue->ExecuteCommandLists(1, command_list);

		const auto fence = fence_list[frame_index];
		if (FAILED(graphic_command_queue->Signal(fence.getNativeFence(), fence.getValue())))
			ConsoleLogger::logCritical(k_dx12_channel, "Unable to signal the fence value!");

		if (FAILED(swap_chain->Present(0, 0)))
			ConsoleLogger::logCritical(k_dx12_channel, "Unable to present!");
	}
	
	void DX12GraphicContext::finalize() noexcept
	{
		for (UInt32 i = 0; i != buffer_count; ++i)
		{
			frame_index = i;
			waitForPreviousFrame();
		}
	}

	void DX12GraphicContext::handleResize() const noexcept
	{
		//TODO
		assert(device);
	}

	void DX12GraphicContext::waitForPreviousFrame() noexcept
	{
		frame_index = swap_chain->GetCurrentBackBufferIndex();
		fence_list[frame_index].wait();
	}


	void DX12GraphicContext::updatePipeline() noexcept
	{
		waitForPreviousFrame();

		if (FAILED(command_allocator_list[frame_index]->Reset()))
			ConsoleLogger::logCritical(k_dx12_channel, "Unable to reset the command allocator");

		if (FAILED(graphic_command_list->Reset(command_allocator_list[frame_index].Get(), NULL)))
			ConsoleLogger::logCritical(k_dx12_channel, "Unable to reset the command allocator");

		const auto rtv_barrier = CD3DX12_RESOURCE_BARRIER::Transition(getCurrentBackBuffer(), D3D12_RESOURCE_STATE_PRESENT, D3D12_RESOURCE_STATE_RENDER_TARGET);
		graphic_command_list->ResourceBarrier(1, &rtv_barrier);

		CD3DX12_CPU_DESCRIPTOR_HANDLE descriptor_handle(rtv_descriptor_heap->GetCPUDescriptorHandleForHeapStart(), frame_index, rtv_descriptor_size);
		graphic_command_list->OMSetRenderTargets(1, &descriptor_handle, FALSE, nullptr);

		const float color[] = { 0.0f, 0.2f, 0.4f, 1.0f };
		graphic_command_list->ClearRenderTargetView(descriptor_handle, color, 0, nullptr);

		const auto state_present_barrier = CD3DX12_RESOURCE_BARRIER::Transition(back_buffer_list[frame_index].Get(), D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATE_PRESENT);
		graphic_command_list->ResourceBarrier(1, &state_present_barrier);

		if (FAILED(graphic_command_list->Close()))
			ConsoleLogger::logCritical(k_dx12_channel, "Unable to close the graphic command list");
	}
}
