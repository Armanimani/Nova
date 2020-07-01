#pragma once

#include "Engine/Common/common.hpp"

#include <string>

namespace nova
{
	struct NOVA_API WindowSettings
	{
		Bool should_create_window{ true };
		void* custom_window_handle{ nullptr };

		Int32 initial_position_x{ 0 };
		Int32 initial_position_y{ 0 };
		Int32 initial_width{ 3840 };
		Int32 initial_height{ 2160 };

		std::string title{ "Nova" };
	};
}
