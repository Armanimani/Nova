#include "Engine/Systems/Graphics/Platform/DirectX12/DX12Common.hpp"
#include "Engine/Systems/Graphics/Platform/DirectX12/DX12FeatureChecker.hpp"
#include "Engine/Systems/Graphics/Platform/DirectX12/DX12DXGIFactoryFactory.hpp"
#include "Engine/Logging/ConsoleLogger.hpp"

namespace nova
{
	Bool DX12FeatureChecker::isTearingSupported() noexcept
	{
		auto result = FALSE;

		auto factory = DX12DXGIFactoryFactory::create();
		if (FAILED(factory->CheckFeatureSupport(DXGI_FEATURE_PRESENT_ALLOW_TEARING, &result, sizeof(result))))
		{
			ConsoleLogger::logCritical(k_dx12_channel, "Unable to get the tearing support");
			return false;
		}
		return true;
	}
}
