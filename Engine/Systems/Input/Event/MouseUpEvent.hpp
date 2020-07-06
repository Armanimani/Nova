#pragma once

#include "Engine/Event/IEvent.hpp"
#include "Engine/Systems/Input/Codes/MouseCode.hpp"

namespace nova
{
	struct NOVA_API MouseUpEvent : public IEvent
	{
		explicit MouseUpEvent(const MouseCode button)
			: button{ button } {}

		MouseCode button{ MouseCode::MOUSE_NO_CODE };
	};
}
