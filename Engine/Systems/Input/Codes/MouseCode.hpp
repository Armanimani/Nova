#pragma once

#include "Engine/Common/common.hpp"

namespace nova
{
	enum struct NOVA_API MouseCode : UInt32
	{
		MOUSE_NO_CODE = 0x00,
		MOUSE_LEFT = 0x01,
		MOUSE_RIGHT = 0x02,
		MOUSE_MIDDLE = 0x03,
		MOUSE_WHEEL = 0x04,
	};

	MouseCode operator|(MouseCode lhs, MouseCode rhs);
	MouseCode operator&(MouseCode lhs, MouseCode rhs);
	MouseCode& operator|=(MouseCode& lhs, MouseCode rhs);
	MouseCode& operator&=(MouseCode& lhs, MouseCode rhs);

	UInt32 operator|(MouseCode lhs, UInt32 rhs);
	UInt32 operator|(UInt32 lhs, MouseCode rhs);
	UInt32 operator&(MouseCode lhs, UInt32 rhs);
	UInt32 operator&(UInt32 lhs, MouseCode rhs);
	UInt32 operator^(MouseCode lhs, UInt32 rhs);
	UInt32 operator^(UInt32 lhs, MouseCode rhs);
}
