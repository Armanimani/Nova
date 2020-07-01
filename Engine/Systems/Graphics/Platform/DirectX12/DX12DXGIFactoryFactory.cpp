#include "Engine/Systems/Graphics/Platform/DirectX12/DX12DXGIFactoryFactory.hpp"
#include "Engine/Logging/ConsoleLogger.hpp"

namespace nova
{
	Microsoft::WRL::ComPtr<IDXGIFactory7> DX12DXGIFactoryFactory::create(const Bool is_debug_enabled) noexcept
	{
		// TODO: Add support for non-debug build
		Microsoft::WRL::ComPtr<IDXGIFactory7> factory{};
		if (is_debug_enabled)
		{
			if (FAILED(CreateDXGIFactory2(DXGI_CREATE_FACTORY_DEBUG, IID_PPV_ARGS(&factory))))
			{
				ConsoleLogger::logCritical(k_dx12_channel, "Unable to create DXGI factory in debug mode!");
			}
		}
		else
		{
			if (FAILED(CreateDXGIFactory2(0, IID_PPV_ARGS(&factory))))
			{
				ConsoleLogger::logCritical(k_dx12_channel, "Unable to create DXGI factory");
			}
		}
		
		return factory;
	}
}
