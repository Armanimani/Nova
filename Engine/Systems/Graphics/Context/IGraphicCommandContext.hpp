#pragma once

#include "Engine/Common/common.hpp"

namespace nova
{
	class NOVA_API IGraphicCommandContext
	{
	public:
		virtual ~IGraphicCommandContext() = default;

		virtual void clearRenderTargetViewColor(Float red, Float green, Float blue, Float alpha) noexcept = 0;
	};
}
