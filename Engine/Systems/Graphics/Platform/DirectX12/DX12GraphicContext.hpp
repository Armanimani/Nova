#pragma once

#include <Windows.h>
#include <vector>
#include <memory>

#include "Engine/Systems/Graphics/Context/IGraphicContext.hpp"
#include "Engine/Systems/Graphics/Settings/GraphicSettings.hpp"
#include "Engine/Systems/Graphics/Platform/DirectX12/DX12CommandList.hpp"
#include "Engine/Systems/Graphics/Platform/DirectX12/DX12CommandAllocator.hpp"
#include "Engine/Systems/Graphics/Platform/DirectX12/DX12Common.hpp"
#include "Engine/Systems/Graphics/Platform/DirectX12/DX12Device.hpp"
#include "Engine/Systems/Graphics/Platform/DirectX12/DX12Fence.hpp"
#include "Engine/Common/common.hpp"

namespace nova
{
	class NOVA_API DX12GraphicContext final: public IGraphicContext
	{
	public:
		DX12GraphicContext(const GraphicSettings& settings, void* window_handle);

		void initialize() noexcept override;
		void present() noexcept override;
		void finalize() noexcept override;


		void handleWindowResizeEvent(UInt32 width, UInt32 height) noexcept override;
	private:
		HWND handle{};
		UInt32 buffer_count{};
		UInt32 frame_index{};
		
		std::unique_ptr<DX12Device> device{ nullptr };
		Microsoft::WRL::ComPtr<IDXGISwapChain4> swap_chain{};
		std::unique_ptr<DX12CommandList> graphic_command_list{};
		Microsoft::WRL::ComPtr<ID3D12CommandQueue> graphic_command_queue{};
		Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> rtv_descriptor_heap{};
		Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> dsv_descriptor_heap{};

		std::vector<Microsoft::WRL::ComPtr<ID3D12Resource1>> back_buffer_list{};
		std::vector<std::unique_ptr<DX12CommandAllocator>> command_allocator_list{};
		std::vector<DX12Fence> fence_list{};

		UInt32 rtv_descriptor_size{};
		UInt32 dsv_descriptor_size{};
		UInt32 cbv_srv_uav_descriptor_size{};

		void createFences() noexcept;
		void createCommandObjects() noexcept;
		void createSwapChain() noexcept;
		void createDescriptorHeaps() noexcept;
		void createRtvAndDsv() noexcept;

		[[nodiscard]] D3D12_CPU_DESCRIPTOR_HANDLE getCurrentBackBufferViewHandle() const noexcept;
		[[nodiscard]] D3D12_CPU_DESCRIPTOR_HANDLE getCurrentDepthStencilViewHandle() const noexcept;
		[[nodiscard]] ID3D12Resource* getCurrentBackBuffer() const noexcept;
		
		void waitForPreviousFrame() noexcept;
		void updatePipeline() noexcept;
		
		void setupViewport(UInt32 width, UInt32 height) const noexcept;
	};
}