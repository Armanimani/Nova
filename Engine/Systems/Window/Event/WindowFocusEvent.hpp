#pragma once

#include "Engine/Event/IEvent.hpp"

namespace nova
{
	struct NOVA_API WindowFocusEvent : public IEvent
	{
		explicit WindowFocusEvent(const Bool is_focused)
			: is_focused{ is_focused } {}
		
		Bool is_focused{ false };
	};
}
