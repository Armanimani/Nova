#pragma once

#include "Engine/Common/common.hpp"
#include "Engine/Systems/Graphics/Platform/DirectX12/DX12Common.hpp"
#include "Engine/Systems/Graphics/Platform/DirectX12/DX12DescriptorHeap.hpp"
#include "Engine/Systems/Graphics/Platform/DirectX12/DX12CommandListManager.hpp"

namespace nova
{
	class NOVA_API DX12Device
	{
	public:
		DX12Device();

		[[nodiscard]] ID3D12Device* getNative() const noexcept;
		
		[[nodiscard]] DX12DescriptorHeap* getRTVDescriptorHeap() const noexcept;
		[[nodiscard]] DX12DescriptorHeap* getDSVDescriptorHeap() const noexcept;
		
		[[nodiscard]] DX12CommandList* getDirectCommandList() const noexcept;
		[[nodiscard]] DX12CommandList* getCopyCommandList() const noexcept;
		[[nodiscard]] DX12CommandList* getComputeCommandList() const noexcept;

		[[nodiscard]] DX12CommandListManager* getDirectCommandListManager() const noexcept;
		[[nodiscard]] DX12CommandListManager* getCopyCommandListManager() const noexcept;
		[[nodiscard]] DX12CommandListManager* getComputeCommandListManager() const noexcept;

		[[nodiscard]] ID3D12CommandQueue* getCommandQueue() const noexcept;
	private:
		Microsoft::WRL::ComPtr<ID3D12Device> device{};
		
		Microsoft::WRL::ComPtr<ID3D12Debug3> debug{};
		Microsoft::WRL::ComPtr<ID3D12InfoQueue> debug_info_queue{};

		std::unique_ptr<DX12CommandListManager> direct_command_list_manager{ nullptr };
		std::unique_ptr<DX12CommandListManager> copy_command_list_manager{ nullptr };
		std::unique_ptr<DX12CommandListManager> compute_command_list_manager{ nullptr };
		
		Microsoft::WRL::ComPtr<ID3D12CommandQueue> graphic_command_queue{};

		std::unique_ptr<DX12DescriptorHeap> rtv_descriptor_heap{ nullptr };
		std::unique_ptr<DX12DescriptorHeap> dsv_descriptor_heap{ nullptr };
		
		void createDevice() noexcept;
		void createDescriptorHeaps() noexcept;
		void createGraphicCommandQueue() noexcept;
		void createCommandListManagers() noexcept;
		
		void enableDebugLayer() noexcept;
		void enableDebugInfoQueue() noexcept;
		
		[[nodiscard]] static D3D12_COMMAND_QUEUE_DESC getCommandQueueDescription(
			D3D12_COMMAND_LIST_TYPE type, D3D12_COMMAND_QUEUE_PRIORITY priority) noexcept;	
	};
}