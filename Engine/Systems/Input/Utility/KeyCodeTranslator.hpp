#pragma once

#include "Engine/Systems/Input/Codes/KeyCode.hpp"

#include <string>
#include <map>

namespace nova
{
	class NOVA_API KeyCodeTranslator
	{
	public:
		static std::string translate(KeyCode key_code) noexcept;
	private:
		static std::map<const KeyCode, std::string> registry;
	};
}
