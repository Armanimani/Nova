#include "Engine/Systems/Graphics/Platform/DirectX12/DX12DXGIFactory.hpp"
#include "Engine/Logging/ConsoleLogger.hpp"

namespace nova
{
	DX12DXGIFactory::DX12DXGIFactory()
	{		
	#ifdef _DEBUG
		if (FAILED(CreateDXGIFactory2(DXGI_CREATE_FACTORY_DEBUG, IID_PPV_ARGS(&dxgi_factory))))
		{
			ConsoleLogger::logCritical(k_dx12_channel, "Unable to create DXGI factory in debug mode!");
		}
	#endif
		
		if (FAILED(CreateDXGIFactory1(IID_PPV_ARGS(&dxgi_factory))))
		{
			ConsoleLogger::logCritical(k_dx12_channel, "Unable to create DXGI factory");
		}
	}

	Bool DX12DXGIFactory::checkSupportTearing() const noexcept
	{
		auto result = FALSE;
		if (FAILED(dxgi_factory->CheckFeatureSupport(DXGI_FEATURE_PRESENT_ALLOW_TEARING, &result, sizeof(result))))
		{
			ConsoleLogger::logCritical(k_dx12_channel, "Unable to get the tearing support");
			return false;
		}
		return true;
	}

	IDXGIFactory6* DX12DXGIFactory::getNative() const noexcept
	{
		return dxgi_factory.Get();
	}
}
