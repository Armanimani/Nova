#pragma once

#include "Engine/Systems/Graphics/Platform/DirectX12/DX12Common.hpp"
#include "Engine/Common/common.hpp"

namespace nova
{
	class NOVA_API DX12DescriptorHeap
	{
	public:
		DX12DescriptorHeap(ID3D12Device* device, D3D12_DESCRIPTOR_HEAP_TYPE type, UInt32 number, D3D12_DESCRIPTOR_HEAP_FLAGS flags);

		[[nodiscard]] UInt32 getNumber() const noexcept;
		[[nodiscard]] UInt32 getSize() const noexcept;
		[[nodiscard]] D3D12_DESCRIPTOR_HEAP_TYPE getType() const noexcept;
		
		[[nodiscard]] D3D12_CPU_DESCRIPTOR_HANDLE getCPUHandle() const noexcept;
		[[nodiscard]] D3D12_CPU_DESCRIPTOR_HANDLE getCPUHandle(UInt32 index) const noexcept;
		[[nodiscard]] D3D12_GPU_DESCRIPTOR_HANDLE getGPUHandle() const noexcept;
		
		[[nodiscard]] ID3D12DescriptorHeap* getNative() const noexcept;
	private:
		Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> heap{};

		UInt32 number{};
		UInt32 size{};
		D3D12_DESCRIPTOR_HEAP_TYPE type{};
		D3D12_CPU_DESCRIPTOR_HANDLE cpu_handle{};
		D3D12_GPU_DESCRIPTOR_HANDLE gpu_handle{};

		[[nodiscard]] static D3D12_DESCRIPTOR_HEAP_DESC getDescription(
			D3D12_DESCRIPTOR_HEAP_TYPE type, UInt32 number, D3D12_DESCRIPTOR_HEAP_FLAGS flags) noexcept;
	};
}

