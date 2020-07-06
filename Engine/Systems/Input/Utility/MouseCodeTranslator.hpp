#pragma once

#include "Engine/Systems/Input/Codes/MouseCode.hpp"

#include <string>
#include <map>

namespace nova
{
	class NOVA_API MouseCodeTranslator
	{
	public:
		static std::string translate(MouseCode mouse_code) noexcept;
	private:
		static std::map<const MouseCode, std::string> registry;
	};
}
