#pragma once

#include "Engine/Event/IEvent.hpp"

namespace nova
{
	struct NOVA_API MouseWheelEvent : public IEvent
	{
		explicit MouseWheelEvent(const Int32 increment)
			: increment{ increment } {}

		Int32 increment{ 0 };
	};
}
