#include "Engine/Systems/Input/Utility/MouseCodeTranslator.hpp"

namespace nova
{
	std::unordered_map<const MouseCode, std::string> MouseCodeTranslator::registry
	{
		{ MouseCode::MOUSE_NO_CODE, "NoCode" },
		{ MouseCode::MOUSE_LEFT, "LeftClick" },
		{ MouseCode::MOUSE_RIGHT, "RightClick" },
		{ MouseCode::MOUSE_MIDDLE, "MiddleClick" },
		{ MouseCode::MOUSE_WHEEL, "WheelRotate" },
	};


	std::string MouseCodeTranslator::translate(const MouseCode mouse_code) noexcept
	{
		return registry[mouse_code];
	}
}
