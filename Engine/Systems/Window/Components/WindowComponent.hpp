#pragma once

#include "Engine/Common/common.hpp"

namespace nova
{
	struct NOVA_API WindowComponent
	{
		Bool own_window{ false };
		void* window_handle{ nullptr };
	};
}