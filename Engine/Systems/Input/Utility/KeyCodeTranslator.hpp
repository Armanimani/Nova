#pragma once

#include "Engine/Systems/Input/Codes/KeyCode.hpp"

#include <string>
#include <unordered_map>

namespace nova
{
	class NOVA_API KeyCodeTranslator
	{
	public:
		static std::string translate(KeyCode key_code) noexcept;
	private:
		static std::unordered_map<const KeyCode, std::string> registry;
	};
}
