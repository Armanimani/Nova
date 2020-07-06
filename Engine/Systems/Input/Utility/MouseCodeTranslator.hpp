#pragma once

#include "Engine/Systems/Input/Codes/MouseCode.hpp"

#include <string>
#include <unordered_map>

namespace nova
{
	class NOVA_API MouseCodeTranslator
	{
	public:
		static std::string translate(MouseCode mouse_code) noexcept;
	private:
		static std::unordered_map<const MouseCode, std::string> registry;
	};
}
