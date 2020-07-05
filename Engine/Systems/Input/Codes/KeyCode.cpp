#include "Engine/Systems/Input/Codes/KeyCode.hpp"

namespace nova
{
	KeyCode operator|(const KeyCode lhs, const KeyCode rhs)
	{
		return static_cast<KeyCode>(static_cast<UInt32>(lhs) | static_cast<UInt32>(rhs));
	}
	
	KeyCode operator&(const KeyCode lhs, const KeyCode rhs)
	{
		return static_cast<KeyCode>(static_cast<UInt32>(lhs) & static_cast<UInt32>(rhs));
	}
	
	KeyCode& operator|=(KeyCode& lhs, const KeyCode rhs)
	{
		lhs = static_cast<KeyCode>(static_cast<UInt32>(lhs) | static_cast<UInt32>(rhs));
		return lhs;
	}
	
	KeyCode& operator&=(KeyCode& lhs, const KeyCode rhs)
	{
		lhs = static_cast<KeyCode>(static_cast<UInt32>(lhs) & static_cast<UInt32>(rhs));
		return lhs;
	}

	UInt32 operator|(const KeyCode lhs, const UInt32 rhs)
	{
		return static_cast<UInt32>(lhs) | rhs;
	}
	
	UInt32 operator|(const UInt32 lhs, const KeyCode rhs)
	{
		return lhs | static_cast<UInt32>(rhs);
	}
	
	UInt32 operator&(const KeyCode lhs, const UInt32 rhs)
	{
		return static_cast<UInt32>(lhs) & rhs;
	}
	
	UInt32 operator&(const UInt32 lhs, const KeyCode rhs)
	{
		return lhs & static_cast<UInt32>(rhs);
	}
	
	UInt32 operator^(const KeyCode lhs, const UInt32 rhs)
	{
		return static_cast<UInt32>(lhs) ^ rhs;
	}
	
	UInt32 operator^(const UInt32 lhs, const KeyCode rhs)
	{
		return lhs ^ static_cast<UInt32>(rhs);
	}
}
