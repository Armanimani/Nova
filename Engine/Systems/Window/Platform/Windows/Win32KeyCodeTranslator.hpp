#pragma once

#include "Engine/Systems/Input/Codes/KeyCode.hpp"

#include <map>

namespace nova
{
	class NOVA_API Win32KeyCodeTranslator
	{
	public:
		static KeyCode translate(const UInt32 native_key) noexcept;
	private:
		static std::map<const UInt32, KeyCode> registry;
	};
}
