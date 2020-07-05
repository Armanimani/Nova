#pragma once

#include "Engine/Event/IEvent.hpp"

namespace nova
{
	struct NOVA_API WindowResizeEvent: public IEvent
	{
		UInt32 width{};
		UInt32 height{};
	};
}
