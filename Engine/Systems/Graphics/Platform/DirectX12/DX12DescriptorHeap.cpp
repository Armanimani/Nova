#include "Engine/Systems/Graphics/Platform/DirectX12/DX12DescriptorHeap.hpp"
#include "Engine/Logging/ConsoleLogger.hpp"

namespace nova
{
	DX12DescriptorHeap::DX12DescriptorHeap(ID3D12Device* device, 
		const D3D12_DESCRIPTOR_HEAP_TYPE type, const UInt32 number, const D3D12_DESCRIPTOR_HEAP_FLAGS flags)
		: number{ number }, type{ type }
	{
		const auto description = getDescription(type, number, flags);
		if (FAILED(device->CreateDescriptorHeap(&description, IID_PPV_ARGS(&heap))))
			ConsoleLogger::logCritical(k_dx12_channel, "Unable to create descriptor heap!");

		size = device->GetDescriptorHandleIncrementSize(type);
		cpu_handle = heap->GetCPUDescriptorHandleForHeapStart();
		gpu_handle = heap->GetGPUDescriptorHandleForHeapStart();
	}

	UInt32 DX12DescriptorHeap::getNumber() const noexcept
	{
		return number;
	}
	UInt32 DX12DescriptorHeap::getSize() const noexcept
	{
		return size;
	}
	
	D3D12_DESCRIPTOR_HEAP_TYPE DX12DescriptorHeap::getType() const noexcept
	{
		return type;
	}
	
	D3D12_CPU_DESCRIPTOR_HANDLE DX12DescriptorHeap::getCPUHandle() const noexcept
	{
		return cpu_handle;
	}

	D3D12_CPU_DESCRIPTOR_HANDLE DX12DescriptorHeap::getCPUHandle(const UInt32 index) const noexcept
	{
		return CD3DX12_CPU_DESCRIPTOR_HANDLE(getCPUHandle(), index, getSize());
	}
	
	D3D12_GPU_DESCRIPTOR_HANDLE DX12DescriptorHeap::getGPUHandle() const noexcept
	{
		return gpu_handle;
	}

	ID3D12DescriptorHeap* DX12DescriptorHeap::getNative() const noexcept
	{
		return heap.Get();
	}

	D3D12_DESCRIPTOR_HEAP_DESC DX12DescriptorHeap::getDescription(
		const D3D12_DESCRIPTOR_HEAP_TYPE type, const UInt32 number, const D3D12_DESCRIPTOR_HEAP_FLAGS flags) noexcept
	{
		D3D12_DESCRIPTOR_HEAP_DESC description{};
		description.Type = type;
		description.NumDescriptors = number;
		description.Flags = flags;

		return description;
	}
}
