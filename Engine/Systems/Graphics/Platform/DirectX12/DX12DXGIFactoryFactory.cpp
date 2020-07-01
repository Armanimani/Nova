#include "Engine/Systems/Graphics/Platform/DirectX12/DX12DXGIFactoryFactory.hpp"
#include "Engine/Logging/ConsoleLogger.hpp"

namespace nova
{
	Microsoft::WRL::ComPtr<IDXGIFactory6> DX12DXGIFactoryFactory::create() noexcept
	{
		Microsoft::WRL::ComPtr<IDXGIFactory6> factory{};
		
	#ifdef _DEBUG
		if (FAILED(CreateDXGIFactory2(DXGI_CREATE_FACTORY_DEBUG, IID_PPV_ARGS(&factory))))
		{
			ConsoleLogger::logCritical(k_dx12_channel, "Unable to create DXGI factory in debug mode!");
		}
	#endif
		
		if (FAILED(CreateDXGIFactory1(IID_PPV_ARGS(&factory))))
		{
			ConsoleLogger::logCritical(k_dx12_channel, "Unable to create DXGI factory");
		}
		
		return factory;
	}
}
