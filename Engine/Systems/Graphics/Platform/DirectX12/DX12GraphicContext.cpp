#include "Engine/Systems/Graphics/Platform/DirectX12/DX12GraphicContext.hpp"
#include "Engine/Logging/ConsoleLogger.hpp"
#include <cassert>

namespace nova
{
	DX12GraphicContext::DX12GraphicContext([[maybe_unused]] const GraphicSettings& settings, void* window_handle)
		: window_handle{ static_cast<HWND>(window_handle) }
	{
		initializeBufferCount(settings.is_triple_buffering_enabled);
	}

	void DX12GraphicContext::initialize() noexcept
	{		
		createFactory();
		createDevice();
		createSwapChain();
		createRTVAndDSV();
		createFences();
	}

	void DX12GraphicContext::update([[maybe_unused]] Context* context, [[maybe_unused]] Float delta_time) noexcept
	{
		updatePipeline();
		clearColor();
	}

	void DX12GraphicContext::createRTVAndDSV() noexcept
	{
		const auto rtv_descriptor_heap = device->getRTVDescriptorHeap();
		CD3DX12_CPU_DESCRIPTOR_HANDLE rtv_handle(rtv_descriptor_heap->getCPUHandle());
		for (UInt32 i = 0; i != buffer_count; ++i)
		{
			back_buffer_list.emplace_back(nullptr);
			const auto result = swap_chain->getNative()->GetBuffer(i, IID_PPV_ARGS(&back_buffer_list[i]));

			if (FAILED(result))
			{
				ConsoleLogger::logCritical(k_dx12_channel, "Unable to getNative the back buffer from swap chain");
			}
	
			device->getNative()->CreateRenderTargetView(back_buffer_list[i].Get(), nullptr, rtv_handle);
			rtv_handle.Offset(rtv_descriptor_heap->getSize());
		}
	}

	void DX12GraphicContext::setupViewport(const UInt32 width, const UInt32 height) const noexcept
	{
		D3D12_VIEWPORT viewport;
		viewport.TopLeftX = 0;
		viewport.TopLeftY = 0;
		viewport.Width = static_cast<Float>(width);
		viewport.Height = static_cast<Float>(height);
		viewport.MinDepth = 0.0f;
		viewport.MaxDepth = 1.0f;
		device->getDirectCommandList()->getNative()->RSSetViewports(1, &viewport);
		// TODO: Define this as a separate graphic command. It should be added to the queue (delayed) and processed when rendering the new frame.
	}

	void DX12GraphicContext::createDevice() noexcept
	{
		device = std::make_unique<DX12Device>();
	}
	void DX12GraphicContext::createFactory() noexcept
	{
		dxgi_factory = std::make_unique<DX12DXGIFactory>();
	}

	void DX12GraphicContext::createSwapChain() noexcept
	{
		swap_chain = std::make_unique<DX12SwapChain>(
			dxgi_factory->getNative(), device->getCommandQueue(), window_handle, 0, 0, buffer_count);
	}

	void DX12GraphicContext::createFences() noexcept
	{
		for (UInt32 i = 0; i != buffer_count; ++i)
		{
			const auto fence = DX12Fence(device->getNative(), 0, D3D12_FENCE_FLAG_NONE);
			fence_list.push_back(std::make_unique<DX12Fence>(device->getNative(), 0, D3D12_FENCE_FLAG_NONE));
		}
	}

	void DX12GraphicContext::initializeBufferCount(const Bool is_triple_buffering_enabled) noexcept
	{
		if (is_triple_buffering_enabled)
			buffer_count = 3;
		else
			buffer_count = 2;
	}

	D3D12_CPU_DESCRIPTOR_HANDLE DX12GraphicContext::getCurrentBackBufferViewHandle() const noexcept
	{
		const auto descriptor_heap = device->getRTVDescriptorHeap();
		return CD3DX12_CPU_DESCRIPTOR_HANDLE(
			descriptor_heap->getCPUHandle(),
			current_frame_index,
			descriptor_heap->getSize()
		);
	}

	ID3D12Resource* DX12GraphicContext::getCurrentBackBuffer() const noexcept
	{
		return back_buffer_list[current_frame_index].Get();
	}

	void DX12GraphicContext::present() noexcept
	{
		transitionCurrentBackBuffer();
		closeCommandLists();

		ID3D12CommandList* const command_list[] =
		{
			device->getDirectCommandList()->getNative(),
			// device->getCopyCommandList()->getNative(),
			// device->getComputeCommandList()->getNative()
		};

		const auto command_queue = device->getCommandQueue();
		command_queue->ExecuteCommandLists(1, command_list);

		const auto fence = getCurrentFence();
		if (FAILED(command_queue->Signal(fence->getNative(), fence->getValue())))
			ConsoleLogger::logCritical(k_dx12_channel, "Unable to signal the fence value!");

		if (FAILED(swap_chain->getNative()->Present(0, 0)))
			ConsoleLogger::logCritical(k_dx12_channel, "Unable to present!");

		advanceFrame();
	}
	
	void DX12GraphicContext::finalize() noexcept
	{

	}

	void DX12GraphicContext::handleWindowResizeEvent(const UInt32 width, const UInt32 height) noexcept
	{
		for (UInt32 i = 0; i != back_buffer_list.size(); ++i)
		{
			back_buffer_list[i].Reset();
		}

		// TODO: The format need to be same as the one the swap chain is created with, this need to be refactored.
		if (FAILED(swap_chain->getNative()->ResizeBuffers(
			buffer_count, width, height, DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH)))
		{
			ConsoleLogger::logCritical(k_dx12_channel, "Unable to resize the back buffers for swap chain");
		}
		
		createRTVAndDSV();
		setupViewport(width, height);
	}

	IGraphicCommandContext* DX12GraphicContext::getCommandContext() noexcept
	{
		return command_context.get();
	}

	void DX12GraphicContext::updatePipeline() noexcept
	{
		waitForCurrentBackBuffer();
		resetCommandLists();
		setCurrentBackBuffer();
	}

	void DX12GraphicContext::setCurrentBackBuffer() const noexcept
	{
		const auto direct_command_list = device->getDirectCommandList();
		const auto current_back_buffer = getCurrentBackBuffer();
		const auto rtv_barrier = CD3DX12_RESOURCE_BARRIER::Transition(current_back_buffer, D3D12_RESOURCE_STATE_PRESENT, D3D12_RESOURCE_STATE_RENDER_TARGET);
		direct_command_list->getNative()->ResourceBarrier(1, &rtv_barrier);
		
		const auto handle = device->getRTVDescriptorHeap()->getCPUHandle(current_frame_index);
		direct_command_list->getNative()->OMSetRenderTargets(1, &handle, FALSE, nullptr);
	}
	
	void DX12GraphicContext::transitionCurrentBackBuffer() const noexcept
	{
		const auto direct_command_list = device->getDirectCommandList();
		const auto current_back_buffer = getCurrentBackBuffer();
		const auto state_present_barrier = CD3DX12_RESOURCE_BARRIER::Transition(current_back_buffer, D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATE_PRESENT);
		direct_command_list->getNative()->ResourceBarrier(1, &state_present_barrier);
	}

	void DX12GraphicContext::resetCommandLists() const noexcept
	{
		device->getDirectCommandListManager()->resetCommandList();
		device->getCopyCommandListManager()->resetCommandList();
		device->getComputeCommandListManager()->resetCommandList();
	}
	void DX12GraphicContext::closeCommandLists() const noexcept
	{
		device->getDirectCommandListManager()->closeCommandList();
		device->getCopyCommandListManager()->closeCommandList();
		device->getComputeCommandListManager()->closeCommandList();
	}

	void DX12GraphicContext::waitForCurrentBackBuffer() noexcept
	{
		auto fence = getCurrentFence();
		fence->wait();
	}

	void DX12GraphicContext::advanceFrame() noexcept
	{
		current_frame_index++;
		current_frame_index = current_frame_index % buffer_count;
	}

	DX12Fence* DX12GraphicContext::getCurrentFence() noexcept
	{
		return fence_list[current_frame_index].get();
	}

	void DX12GraphicContext::clearColor() const noexcept
	{
		const auto direct_command_list = device->getDirectCommandList();
		const auto handle = device->getRTVDescriptorHeap()->getCPUHandle(current_frame_index);
		
		const float color[] = { 0.0f, 0.2f, 0.4f, 1.0f };
		direct_command_list->getNative()->ClearRenderTargetView(handle, color, 0, nullptr);
	}
}
