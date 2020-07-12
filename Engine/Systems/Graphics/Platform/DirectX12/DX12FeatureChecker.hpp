#pragma once

#include "Engine/Common/common.hpp"
#include "Engine/Systems/Graphics/Platform/DirectX12/DX12Common.hpp"

namespace nova
{
	class NOVA_API DX12FeatureChecker
	{
	public:
		[[nodiscard]] static Bool checkSupportTearing(IDXGIFactory6* factory) noexcept;
		[[nodiscard]] static Bool checkSupportRayTracingTier(ID3D12Device* device) noexcept;
	};
}