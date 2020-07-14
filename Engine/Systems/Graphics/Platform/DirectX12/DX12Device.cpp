#include "Engine/Systems/Graphics/Platform/DirectX12/DX12Device.hpp"
#include "Engine/Logging/ConsoleLogger.hpp"

namespace nova
{
	constexpr auto k_maximum_descriptor_heap_size = 1024;
	constexpr auto k_number_of_allocators = 3;
	
	DX12Device::DX12Device()
	{
	#ifdef _DEBUG
		enableDebugLayer();
	#endif

		createDevice();
		
	#ifdef _DEBUG
		enableDebugInfoQueue();
	#endif

		createDescriptorHeaps();
		createGraphicCommandQueue();
		createCommandListManagers();
	}

	ID3D12Device* DX12Device::getNative() const noexcept
	{
		return device.Get();
	}

	DX12DescriptorHeap* DX12Device::getRTVDescriptorHeap() const noexcept
	{
		return rtv_descriptor_heap.get();
	}
	
	DX12DescriptorHeap* DX12Device::getDSVDescriptorHeap() const noexcept
	{
		return dsv_descriptor_heap.get();
	}

	DX12CommandList* DX12Device::getDirectCommandList() const noexcept
	{
		return direct_command_list_manager->getCommandList();
	}

	DX12CommandList* DX12Device::getCopyCommandList() const noexcept
	{
		return copy_command_list_manager->getCommandList();
	}

	DX12CommandList* DX12Device::getComputeCommandList() const noexcept
	{
		return compute_command_list_manager->getCommandList();
	}

	DX12CommandListManager* DX12Device::getDirectCommandListManager() const noexcept
	{
		return direct_command_list_manager.get();
	}
	
	DX12CommandListManager* DX12Device::getCopyCommandListManager() const noexcept
	{
		return copy_command_list_manager.get();
	}
	
	DX12CommandListManager* DX12Device::getComputeCommandListManager() const noexcept
	{
		return compute_command_list_manager.get();
	}

	ID3D12CommandQueue* DX12Device::getCommandQueue() const noexcept
	{
		return graphic_command_queue.Get();
	}

	void DX12Device::createDescriptorHeaps() noexcept
	{
		rtv_descriptor_heap = std::make_unique<DX12DescriptorHeap>(
			device.Get(), D3D12_DESCRIPTOR_HEAP_TYPE_RTV, k_maximum_descriptor_heap_size, D3D12_DESCRIPTOR_HEAP_FLAG_NONE);
		dsv_descriptor_heap = std::make_unique<DX12DescriptorHeap>(
			device.Get(), D3D12_DESCRIPTOR_HEAP_TYPE_DSV, k_maximum_descriptor_heap_size, D3D12_DESCRIPTOR_HEAP_FLAG_NONE);
	}

	void DX12Device::createGraphicCommandQueue() noexcept
	{
		const auto description = getCommandQueueDescription(D3D12_COMMAND_LIST_TYPE_DIRECT, D3D12_COMMAND_QUEUE_PRIORITY_NORMAL);
		device->CreateCommandQueue(&description, IID_PPV_ARGS(&graphic_command_queue));
	}

	void DX12Device::createCommandListManagers() noexcept
	{
		direct_command_list_manager = std::make_unique<DX12CommandListManager>(getNative(), D3D12_COMMAND_LIST_TYPE_DIRECT, k_number_of_allocators);
		copy_command_list_manager = std::make_unique<DX12CommandListManager>(getNative(), D3D12_COMMAND_LIST_TYPE_COPY, k_number_of_allocators);
		compute_command_list_manager = std::make_unique<DX12CommandListManager>(getNative(), D3D12_COMMAND_LIST_TYPE_COMPUTE, k_number_of_allocators);
	}

	void DX12Device::createDevice() noexcept
	{
		if (FAILED(D3D12CreateDevice(nullptr, D3D_FEATURE_LEVEL_12_1, IID_PPV_ARGS(&device))))
			ConsoleLogger::logCritical(k_dx12_channel, "Unable to create DirectX12 device!");
	}
	
	void DX12Device::enableDebugLayer() noexcept
	{
		if (FAILED(D3D12GetDebugInterface(IID_PPV_ARGS(&debug))))
		{
			ConsoleLogger::logWarning(k_dx12_channel, "Unable to enable debug interface!");
		}
		debug->EnableDebugLayer();
	}
	
	void DX12Device::enableDebugInfoQueue() noexcept
	{
		if (FAILED(device.As(&debug_info_queue)))
			ConsoleLogger::logWarning(k_dx12_channel, "Unable to query the info queue");
	
		debug_info_queue->SetBreakOnSeverity(D3D12_MESSAGE_SEVERITY_CORRUPTION, true);
		debug_info_queue->SetBreakOnSeverity(D3D12_MESSAGE_SEVERITY_ERROR, true);
		debug_info_queue->SetBreakOnSeverity(D3D12_MESSAGE_SEVERITY_WARNING, true);
	}

	D3D12_COMMAND_QUEUE_DESC DX12Device::getCommandQueueDescription(
		const D3D12_COMMAND_LIST_TYPE type,
		const D3D12_COMMAND_QUEUE_PRIORITY priority) noexcept
	{
		D3D12_COMMAND_QUEUE_DESC description;
		description.Type = type;
		description.Priority = priority;
		description.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
		description.NodeMask = 0;

		return description;
	}
}
