#pragma once

#include "Engine/Systems/Graphics/Platform/DirectX12/DX12Common.hpp"
#include "Engine/Systems/Graphics/Context/IGraphicCommandContext.hpp"
#include "Engine/Systems/Graphics/Platform/DirectX12/DX12Device.hpp"
#include "Engine/Systems/Graphics/Platform/DirectX12/DX12SwapChain.hpp"

namespace nova
{
	class NOVA_API DX12CommandContext : public IGraphicCommandContext
	{
	public:
		void setSwapChain(DX12SwapChain* swap_chain) noexcept;
		void setDevice(DX12Device* device) noexcept;
		void setCurrentFrameIndex(UInt32 current_frame_index);
		
		void clearRenderTargetViewColor(Float red, Float green, Float blue, Float alpha) noexcept override;
	private:
		UInt32 current_frame_index{};
		DX12Device* device{ nullptr };
		DX12SwapChain* swap_chain{ nullptr };
	};
}
