#include "Engine/Logging/ConsoleLogger.hpp"
#include "Engine/Application/Application.hpp"
#include "Engine/Systems/ISystem.hpp"
#include "Engine/Systems/Window/WindowSystem.hpp"
#include "Engine/Systems/Input/InputSystem.hpp"
#include "Engine/Systems/Graphics/GraphicSystem.hpp"
#include "Engine/Systems/Window/Settings/WindowSettings.hpp"
#include "Engine/Systems/Exit/ExitSystem.hpp"
#include "Engine/Systems/Graphics/Settings/GraphicSettings.hpp"
#include <string>

constexpr const char* k_sandbox_channel = "Sandbox";

class FPSSystem : public nova::ISystem
{
public:

	void configure([[maybe_unused]] nova::Context* context) override
	{
		
	}

	void initialize([[maybe_unused]] nova::Context* context) noexcept override
	{
		nova::ConsoleLogger::logInformation(k_sandbox_channel, "FPSSystem initialized!");
	}

	void update([[maybe_unused]] nova::Context* context, const nova::Float delta_time) noexcept override
	{
		frame_count++;
		total_duration += delta_time;

		if (total_duration > 1.0f)
		{
			nova::ConsoleLogger::logInformation(k_sandbox_channel, "FPS: " + std::to_string(frame_count));
			total_duration -= 1.0f;
			frame_count = 0;
		}
	}

	void finalize([[maybe_unused]] nova::Context* context) noexcept override
	{
		nova::ConsoleLogger::logInformation(k_sandbox_channel, "FPSSystem finalized!");
	}
private:
	nova::Float total_duration{};
	nova::UInt32 frame_count{};
};



int main()
{
	nova::ConsoleLogger::enableLoggingLevel(nova::ConsoleLogger::LoggingLevel::critical);
	nova::ConsoleLogger::enableLoggingLevel(nova::ConsoleLogger::LoggingLevel::warning);
	nova::ConsoleLogger::enableLoggingLevel(nova::ConsoleLogger::LoggingLevel::information);
	nova::ConsoleLogger::enableLoggingLevel(nova::ConsoleLogger::LoggingLevel::debug);

	nova::Application application{};
	auto fps_system = std::make_unique<FPSSystem>();
	application.addSystem(std::move(fps_system));

	const auto window_settings = nova::WindowSettings();
	application.addSettings(window_settings);
	application.addSystem(std::make_unique<nova::WindowSystem>());

	application.addSystem(std::make_unique<nova::InputSystem>());
	
	auto graphic_settings = nova::GraphicSettings();
	graphic_settings.api = nova::GraphicApi::direct_x12;
	application.addSettings(graphic_settings);
	application.addSystem(std::make_unique<nova::GraphicSystem>());

	application.addSystem(std::make_unique<nova::ExitSystem>());
	
	application.start();
}