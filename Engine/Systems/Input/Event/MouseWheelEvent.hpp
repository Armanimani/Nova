#pragma once

#include "Engine/Event/IEvent.hpp"

namespace nova
{
	struct NOVA_API MouseUpEvent : public IEvent
	{
		explicit MouseUpEvent(const Int32 increment)
			: increment{ increment } {}

		Int32 increment{ 0 };
	};
}
