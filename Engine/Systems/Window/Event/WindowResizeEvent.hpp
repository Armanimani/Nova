#pragma once

#include "Engine/Event/IEvent.hpp"

namespace nova
{
	struct NOVA_API WindowResizeEvent: public IEvent
	{
		WindowResizeEvent(const UInt32 width, const UInt32 height)
			: width{ width }, height{ height }{}
		
		UInt32 width{};
		UInt32 height{};
	};
}
