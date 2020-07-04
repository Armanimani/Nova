#pragma once

#include <Engine/Systems/Graphics/Settings/GraphicSettings.hpp>

namespace nova::editor
{
	struct EngineSettings
	{
		void* window_handle{ nullptr };
		GraphicApi graphic_api{};
	};
}