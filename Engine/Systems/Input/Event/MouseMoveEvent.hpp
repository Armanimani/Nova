#pragma once

#include "Engine/Event/IEvent.hpp"

namespace nova
{
	struct NOVA_API MouseMoveEvent : public IEvent
	{
		MouseMoveEvent(const Int32 position_x, const Int32 position_y)
			: position_x{ position_x }, position_y{ position_y }{}

		Int32 position_x{};
		Int32 position_y{};
	};
}
