#pragma once

#include "Engine/Common/common.hpp"

namespace nova
{
	enum class NOVA_API GraphicApi
	{
		none,
		direct_x12,
	};
	
	struct NOVA_API GraphicSettings
	{
		Bool is_v_sync_enabled{ false };
		Bool is_triple_buffering_enabled{ false };
		GraphicApi api{ GraphicApi::none };
	};
}
