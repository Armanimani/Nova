#pragma once

#include "Engine/Event/IEvent.hpp"
#include "Engine/Systems/Input/Codes/KeyCode.hpp"

namespace nova
{
	struct NOVA_API KeyUpEvent : public IEvent
	{
		explicit KeyUpEvent(const KeyCode key)
			: key{ key } {}

		KeyCode key{ KeyCode::KEY_NO_CODE };
	};
}
