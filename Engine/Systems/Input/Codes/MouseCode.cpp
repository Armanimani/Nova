#include "Engine/Systems/Input/Codes/MouseCode.hpp"

namespace nova
{
	MouseCode operator|(const MouseCode lhs, const MouseCode rhs)
	{
		return static_cast<MouseCode>(static_cast<UInt32>(lhs) | static_cast<UInt32>(rhs));
	}

	MouseCode operator&(const MouseCode lhs, const MouseCode rhs)
	{
		return static_cast<MouseCode>(static_cast<UInt32>(lhs) & static_cast<UInt32>(rhs));
	}

	MouseCode& operator|=(MouseCode& lhs, const MouseCode rhs)
	{
		lhs = static_cast<MouseCode>(static_cast<UInt32>(lhs) | static_cast<UInt32>(rhs));
		return lhs;
	}

	MouseCode& operator&=(MouseCode& lhs, const MouseCode rhs)
	{
		lhs = static_cast<MouseCode>(static_cast<UInt32>(lhs) & static_cast<Int32>(rhs));
		return lhs;
	}

	UInt32 operator|(const MouseCode lhs, const UInt32 rhs)
	{
		return static_cast<UInt32>(lhs) | rhs;
	}

	UInt32 operator|(const UInt32 lhs, const MouseCode rhs)
	{
		return lhs | static_cast<UInt32>(rhs);
	}

	UInt32 operator&(const MouseCode lhs, const UInt32 rhs)
	{
		return static_cast<UInt32>(lhs) & rhs;
	}

	UInt32 operator&(const UInt32 lhs, const MouseCode rhs)
	{
		return lhs & static_cast<UInt32>(rhs);
	}

	UInt32 operator^(const MouseCode lhs, const UInt32 rhs)
	{
		return static_cast<UInt32>(lhs) ^ rhs;
	}

	UInt32 operator^(const UInt32 lhs, const MouseCode rhs)
	{
		return lhs ^ static_cast<UInt32>(rhs);
	}


	UInt32 operator!(const MouseCode mouse_code)
	{
		return !static_cast<UInt32>(mouse_code);
	}
};
