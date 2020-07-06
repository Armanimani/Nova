#pragma once

#include "Engine/Event/IEvent.hpp"
#include "Engine/Systems/Input/Codes/KeyCode.hpp"

namespace nova
{
	struct NOVA_API KeyDownEvent : public IEvent
	{
		explicit KeyDownEvent(const KeyCode key)
			: key{ key }{}
		
		KeyCode key{ KeyCode::KEY_NO_CODE };
	};
}
