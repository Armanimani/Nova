#include "Engine/Systems/Graphics/Platform/DirectX12/DX12SwapChain.hpp"
#include "Engine/Systems/Graphics/Platform/DirectX12/DX12FeatureChecker.hpp"
#include "Engine/Logging/ConsoleLogger.hpp"

namespace nova
{
	DX12SwapChain::DX12SwapChain(IDXGIFactory6* factory, ID3D12CommandQueue* command_queue,
		HWND window_handle, const UInt32 resolution_x, const UInt32 resolution_y, const UInt32 buffer_count) noexcept
	{
		Microsoft::WRL::ComPtr<IDXGISwapChain1> swap_chain1;
		const auto descriptor = getDescriptor(factory, resolution_x, resolution_y, buffer_count);
		if (!SUCCEEDED(factory->CreateSwapChainForHwnd(command_queue, window_handle, &descriptor, nullptr, nullptr, &swap_chain1)))
		{
			ConsoleLogger::logCritical(k_dx12_channel, "Unable to create swap chain");
		}

		// Disable the alt-enter for exclusive full-screen
		if (!SUCCEEDED(factory->MakeWindowAssociation(window_handle, DXGI_MWA_NO_ALT_ENTER)))
		{
			ConsoleLogger::logCritical(k_dx12_channel, "Unable to disable the alt-enter combination for exclusive full-screen");
		}

		// Convert the swap chain to type 4
		if (!SUCCEEDED(swap_chain1.As(&swap_chain)))
		{
			ConsoleLogger::logCritical(k_dx12_channel,"Unable to convert swap chain of type 1 to type 4");
		}
	}

	IDXGISwapChain4* DX12SwapChain::getNative() const noexcept
	{
		return swap_chain.Get();
	}

	DXGI_SWAP_CHAIN_DESC1 DX12SwapChain::getDescriptor(
		IDXGIFactory6* factory, const UInt32 resolution_x, const UInt32 resolution_y, const UInt32 buffer_count) noexcept
	{
		DXGI_SWAP_CHAIN_DESC1 descriptor;
		descriptor.Width = resolution_x;
		descriptor.Height = resolution_y;
		descriptor.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		descriptor.Stereo = FALSE;
		descriptor.SampleDesc.Count = 1;
		descriptor.SampleDesc.Quality = 0;
		descriptor.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT | DXGI_USAGE_SHADER_INPUT;
		descriptor.BufferCount = buffer_count;
		descriptor.Scaling = DXGI_SCALING_STRETCH;
		descriptor.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
		descriptor.AlphaMode = DXGI_ALPHA_MODE_UNSPECIFIED;
		descriptor.Flags = DX12FeatureChecker::checkSupportTearing(factory) ? DXGI_SWAP_CHAIN_FLAG_ALLOW_TEARING : 0;

		return descriptor;
	}
}
