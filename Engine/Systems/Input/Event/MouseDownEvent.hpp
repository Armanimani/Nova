#pragma once

#include "Engine/Event/IEvent.hpp"
#include "Engine/Systems/Input/Codes/MouseCode.hpp"

namespace nova
{
	struct NOVA_API MouseDownEvent : public IEvent
	{
		explicit MouseDownEvent(const MouseCode button)
			: button{ button } {}

		MouseCode button{ MouseCode::MOUSE_NO_CODE };
	};
}
