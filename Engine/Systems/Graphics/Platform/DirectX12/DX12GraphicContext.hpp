#pragma once

#include <vector>
#include <memory>

#include "Engine/Systems/Graphics/Context/IGraphicContext.hpp"
#include "Engine/Systems/Graphics/Settings/GraphicSettings.hpp"
#include "Engine/Systems/Graphics/Platform/DirectX12/DX12Common.hpp"
#include "Engine/Systems/Graphics/Platform/DirectX12/DX12CommandContext.hpp"
#include "Engine/Systems/Graphics/Platform/DirectX12/DX12Device.hpp"
#include "Engine/Systems/Graphics/Platform/DirectX12/DX12DXGIFactory.hpp"
#include "Engine/Systems/Graphics/Platform/DirectX12/DX12SwapChain.hpp"
#include "Engine/Systems/Graphics/Platform/DirectX12/DX12Fence.hpp"
#include "Engine/Common/common.hpp"

namespace nova
{
	class NOVA_API DX12GraphicContext final: public IGraphicContext
	{
	public:
		DX12GraphicContext(const GraphicSettings& settings, void* window_handle);

		void initialize() noexcept override;
		void update(Context* context, Float delta_time) noexcept override;
		void present() noexcept override;
		void finalize() noexcept override;
		
		void handleWindowResizeEvent(UInt32 width, UInt32 height) noexcept override;

		IGraphicCommandContext* getCommandContext() noexcept override;
	private:
		HWND window_handle{};
		UInt32 buffer_count{};	
		UInt32 current_frame_index{};
		
		std::unique_ptr<DX12Device> device{ nullptr };
		std::unique_ptr<DX12DXGIFactory> dxgi_factory{ nullptr };
		std::unique_ptr<DX12SwapChain> swap_chain{ nullptr };
		
		std::vector<std::unique_ptr<DX12Fence>> fence_list{};
		std::vector<Microsoft::WRL::ComPtr<ID3D12Resource1>> back_buffer_list{};

		std::unique_ptr<IGraphicCommandContext> command_context{};

		[[nodiscard]] D3D12_CPU_DESCRIPTOR_HANDLE getCurrentBackBufferViewHandle() const noexcept;
		[[nodiscard]] ID3D12Resource* getCurrentBackBuffer() const noexcept;
		
		void setupViewport(UInt32 width, UInt32 height) const noexcept;

		void createDevice() noexcept;
		void createFactory() noexcept;
		void createSwapChain() noexcept;
		void createFences() noexcept;
		void createRTVAndDSV() noexcept;

		void initializeBufferCount(Bool is_triple_buffering_enabled) noexcept;

		void updatePipeline() noexcept;
		void updateCommandContext() const noexcept;

		void setCurrentBackBuffer() const noexcept;
		void transitionCurrentBackBuffer() const noexcept;
		
		void resetCommandLists() const noexcept;
		void closeCommandLists() const noexcept;
		
		void waitForCurrentBackBuffer() noexcept;
		void advanceFrame() noexcept;
		[[nodiscard]] DX12Fence* getCurrentFence() noexcept;

	};
}