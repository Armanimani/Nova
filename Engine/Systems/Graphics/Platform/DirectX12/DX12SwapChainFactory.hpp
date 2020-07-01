#pragma once

#include "Engine/Systems/Graphics/Platform/DirectX12/DX12Common.hpp"
#include "Engine/Common/common.hpp"

namespace nova
{
	class NOVA_API DX12SwapChainFactory
	{
	public:
		[[nodiscard]] static Microsoft::WRL::ComPtr<IDXGISwapChain4> create(
			Microsoft::WRL::ComPtr<ID3D12CommandQueue>& command_queue, HWND window_handle, UInt32 resolution_x, UInt32 resolution_y, 
			UInt32 buffer_count) noexcept;
	private:
		[[nodiscard]] static DXGI_SWAP_CHAIN_DESC1 getDescriptor(UInt32 resolution_x, UInt32 resolution_y, UInt32 buffer_count) noexcept;
	};
}