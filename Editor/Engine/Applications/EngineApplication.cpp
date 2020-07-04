#include "Editor/Engine/Applications/EngineApplication.hpp"
#include <Engine/Systems/Window/WindowSystem.hpp>
#include <Engine/Systems/Window/Settings/WindowSettings.hpp>
#include <Engine/Systems/Graphics/GraphicSystem.hpp>
#include <Engine/Systems/Graphics/Settings/GraphicSettings.hpp>

namespace nova::editor
{
	EngineApplication::EngineApplication(const EngineSettings settings)
		: settings{ settings }
	{
		application = std::make_unique<Application>();

		WindowSettings window_settings;
		window_settings.custom_window_handle = settings.window_handle;
		window_settings.should_create_window = false;
		application->addSettings<WindowSettings>(window_settings);
		application->addSystem(std::make_unique<WindowSystem>());

		GraphicSettings graphic_settings;
		graphic_settings.api = settings.graphic_api;
		graphic_settings.is_triple_buffering_enabled = true;
		graphic_settings.is_v_sync_enabled = false;
		application->addSettings<GraphicSettings>(graphic_settings);
		application->addSystem(std::make_unique<GraphicSystem>());
	}

	EngineApplication::~EngineApplication()
	{
		//TODO: Force terminate the engine before attempting to close it. Also join the thread
	}

	void EngineApplication::start()
	{
		thread = std::make_unique<std::thread>([this]()
			{
				this->application->start();
			}
		);
	}
}
