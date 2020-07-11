#pragma once

#include "Engine/Common/common.hpp"
#include "Engine/Systems/Graphics/Platform/DirectX12/DX12Common.hpp"

namespace nova
{
	class NOVA_API DX12Device
	{
	public:
		explicit DX12Device();

		[[nodiscard]] Microsoft::WRL::ComPtr<ID3D12CommandQueue>createCommandQueue(
			D3D12_COMMAND_LIST_TYPE type, D3D12_COMMAND_QUEUE_PRIORITY priority) const noexcept;

		[[nodiscard]] Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> createDescriptorHeap(
			D3D12_DESCRIPTOR_HEAP_TYPE type, UInt32 number) const noexcept;	
		[[nodiscard]] Microsoft::WRL::ComPtr<ID3D12QueryHeap> createQueryHeap(
			D3D12_QUERY_HEAP_TYPE type, UInt32 number) const noexcept;

		[[nodiscard]] UInt32 getRtvDescriptorSize() const noexcept;
		[[nodiscard]] UInt32 getDsvDescriptorSize() const noexcept;
		[[nodiscard]] UInt32 getCbvSrvUavDescriptorSize() const noexcept;

		[[nodiscard]] ID3D12Device* get() const noexcept;
	private:
		Microsoft::WRL::ComPtr<ID3D12Device> device{};
		Microsoft::WRL::ComPtr<ID3D12Debug3> debug{};
		Microsoft::WRL::ComPtr<ID3D12InfoQueue> debug_info_queue{};

		void createDevice() noexcept;
		void enableDebugLayer() noexcept;
		void enableDebugInfoQueue() noexcept;

		[[nodiscard]] UInt32 getDescriptorSize(D3D12_DESCRIPTOR_HEAP_TYPE type) const noexcept;
		
		[[nodiscard]] static D3D12_COMMAND_QUEUE_DESC getCommandQueueDescription(
			D3D12_COMMAND_LIST_TYPE type, D3D12_COMMAND_QUEUE_PRIORITY priority) noexcept;	
		[[nodiscard]] static D3D12_DESCRIPTOR_HEAP_DESC getDescriptorHeapDescription(
			D3D12_DESCRIPTOR_HEAP_TYPE type, UInt32 number) noexcept;	
		[[nodiscard]] static D3D12_QUERY_HEAP_DESC getQueryHeapDescription(
			D3D12_QUERY_HEAP_TYPE type, UInt32 number) noexcept;	
	};
}