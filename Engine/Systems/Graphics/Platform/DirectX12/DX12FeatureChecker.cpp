#include "Engine/Systems/Graphics/Platform/DirectX12/DX12FeatureChecker.hpp"
#include "Engine/Logging/ConsoleLogger.hpp"

namespace nova
{
	Bool DX12FeatureChecker::checkSupportTearing(IDXGIFactory6* factory) noexcept
	{
		auto result = FALSE;
		if (FAILED(factory->CheckFeatureSupport(DXGI_FEATURE_PRESENT_ALLOW_TEARING, &result, sizeof(result))))
		{
			ConsoleLogger::logCritical(k_dx12_channel, "Unable to get the tearing support");
			return false;
		}
		return true;
	}
	
	Bool DX12FeatureChecker::checkSupportRayTracingTier(ID3D12Device* device) noexcept
	{
		D3D12_FEATURE_DATA_D3D12_OPTIONS5 features{};

		if (FAILED(device->CheckFeatureSupport(D3D12_FEATURE_D3D12_OPTIONS5, &features, sizeof(features))))
		{
			ConsoleLogger::logCritical(k_dx12_channel, "Unable to get the ray tracing support");
			return false;
		}
		return features.RaytracingTier == D3D12_RAYTRACING_TIER_1_0;
	}
}