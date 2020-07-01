#include "Engine/Systems/Graphics/Platform/DirectX12/DX12Device.hpp"
#include "Engine/Logging/ConsoleLogger.hpp"

namespace nova
{
	DX12Device::DX12Device(const Bool is_debug_enabled)
	{
		if (is_debug_enabled)
		{
			enableDebugLayer();
		}
			
		createDevice();
		
		if (is_debug_enabled)
			enableDebugInfoQueue();
	}

	Microsoft::WRL::ComPtr<ID3D12CommandQueue> DX12Device::createCommandQueue(
		const D3D12_COMMAND_LIST_TYPE type, 
		const D3D12_COMMAND_QUEUE_PRIORITY priority) const noexcept
	{
		const auto descriptor = getCommandQueueDescription(type, priority);
		Microsoft::WRL::ComPtr<ID3D12CommandQueue> command_queue{};

		if (FAILED(device->CreateCommandQueue(&descriptor, IID_PPV_ARGS(&command_queue))))
			ConsoleLogger::logCritical(k_dx12_channel, "Unable to create the command queue!");

		return command_queue;
	}

	Microsoft::WRL::ComPtr<ID3D12CommandAllocator> DX12Device::createCommandAllocator(
		const D3D12_COMMAND_LIST_TYPE type) const noexcept
	{
		Microsoft::WRL::ComPtr<ID3D12CommandAllocator> command_allocator{};

		if (FAILED(device->CreateCommandAllocator(type, IID_PPV_ARGS(&command_allocator))))
			ConsoleLogger::logCritical(k_dx12_channel, "Unable to create command allocator!");

		return command_allocator;
	}


	Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> DX12Device::createCommandList(
		const D3D12_COMMAND_LIST_TYPE type,
		const Microsoft::WRL::ComPtr<ID3D12CommandAllocator>& allocator) const noexcept
	{
		Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> command_list{};

		if (FAILED(device->CreateCommandList(0, type, allocator.Get(), nullptr, IID_PPV_ARGS(&command_list))))
			ConsoleLogger::logCritical(k_dx12_channel, "Unable to create the command list!");

		command_list->Close();
		return command_list;
	}

	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> DX12Device::createDescriptorHeap(
		const D3D12_DESCRIPTOR_HEAP_TYPE type,
		const UInt32 number) const noexcept
	{
		const auto description = getDescriptorHeapDescription(type, number);
		Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> descriptor_heap{};
		
		if (FAILED(device->CreateDescriptorHeap(&description, IID_PPV_ARGS(&descriptor_heap))))
			ConsoleLogger::logCritical(k_dx12_channel, "Unable to create descriptor heap!");

		return descriptor_heap;
	}

	Microsoft::WRL::ComPtr<ID3D12QueryHeap> DX12Device::createQueryHeap(
		const D3D12_QUERY_HEAP_TYPE type,
		const UInt32 number) const noexcept
	{
		const auto description = getQueryHeapDescription(type, number);
		Microsoft::WRL::ComPtr<ID3D12QueryHeap> descriptor{};

		if (FAILED(device->CreateQueryHeap(&description, IID_PPV_ARGS(&descriptor))))
			ConsoleLogger::logCritical(k_dx12_channel, "Unable to create descriptor heap!");

		return descriptor;
	}

	UInt32 DX12Device::getRtvDescriptorSize() const noexcept
	{
		return getDescriptorSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
	}
	
	UInt32 DX12Device::getDsvDescriptorSize() const noexcept
	{
		return getDescriptorSize(D3D12_DESCRIPTOR_HEAP_TYPE_DSV);
	}
	
	UInt32 DX12Device::getCbvSrvUavDescriptorSize() const noexcept
	{
		return getDescriptorSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);
	}

	ID3D12Device* DX12Device::getNative() const noexcept
	{
		return device.Get();
	}

	UInt32 DX12Device::getDescriptorSize(const D3D12_DESCRIPTOR_HEAP_TYPE type) const noexcept
	{
		return device->GetDescriptorHandleIncrementSize(type);
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

	D3D12_DESCRIPTOR_HEAP_DESC DX12Device::getDescriptorHeapDescription(
		const D3D12_DESCRIPTOR_HEAP_TYPE type,
		const UInt32 number) noexcept
	{
		D3D12_DESCRIPTOR_HEAP_DESC description{};
		description.Type = type;
		description.NumDescriptors = number;

		return description;
	}

	D3D12_QUERY_HEAP_DESC DX12Device::getQueryHeapDescription(
		const D3D12_QUERY_HEAP_TYPE type,
		const UInt32 number) noexcept
	{
		D3D12_QUERY_HEAP_DESC description{};
		description.Type = type;
		description.Count = number;

		return description;
	}
}
