#pragma once

#include "Engine/Systems/Graphics/Platform/DirectX12/DX12Common.hpp"
#include "Engine/Common/common.hpp"

namespace nova
{
	class NOVA_API DX12SwapChain
	{
	public:
		DX12SwapChain(IDXGIFactory6* factory, ID3D12CommandQueue* command_queue, 
			HWND window_handle, UInt32 resolution_x, UInt32 resolution_y, UInt32 buffer_count) noexcept;

		IDXGISwapChain4* getNative() const noexcept;
	private:
		Microsoft::WRL::ComPtr<IDXGISwapChain4> swap_chain{};

		static DXGI_SWAP_CHAIN_DESC1 getDescriptor(IDXGIFactory6* factory, 
			UInt32 resolution_x, UInt32 resolution_y, UInt32 buffer_count) noexcept;
	};
}