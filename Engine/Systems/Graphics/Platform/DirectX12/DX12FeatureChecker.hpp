#pragma once

#include "Engine/Common/common.hpp"

namespace nova
{
	class NOVA_API DX12FeatureChecker
	{
	public:
		[[nodiscard]] static Bool isTearingSupported() noexcept;
	};
}