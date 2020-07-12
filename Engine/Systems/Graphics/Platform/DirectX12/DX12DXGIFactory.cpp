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

	IDXGIFactory6* DX12DXGIFactory::getNative() const noexcept
	{
		return dxgi_factory.Get();
	}
}
