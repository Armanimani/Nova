#include "Engine/Application/Application.hpp"
#include "Engine/Logging/ConsoleLogger.hpp"
#include "Engine/Time/StopWatch.hpp"
#include "Engine/Time/Clock.hpp"
#include "Engine/DesignPatterns/ServiceLocator.hpp"
#include "Engine/Logging/IConsoleLoggerAdapter.hpp"
#include "Engine/Logging/Implementation/spdlog/ConsoleLoggerAdapter_SpdLog.hpp"

#include <string>


namespace nova
{
	Application::Application()
	{
		context = std::make_unique<Context>();
		ServiceLocator<IConsoleLoggerAdapter>::provide(std::make_unique<ConsoleLoggerAdapter_SpdLog>());
	}

	void Application::addSystem(std::unique_ptr<ISystem>&& pipeline)
	{
		systems.push_back(std::move(pipeline));
	}

	void Application::start() noexcept
	{
		ConsoleLogger::logInformation(k_engine_channel, "Starting...");

		configure();
		initialize();
		update();
		finalize();
	}

	void Application::configure() noexcept
	{
		ConsoleLogger::logInformation(k_engine_channel, "Configuring...");
		configureSystems();
	}

	void Application::initialize() noexcept
	{
		auto stop_watch = StopWatch();
		stop_watch.start();
		
		ConsoleLogger::logInformation(k_engine_channel, "Initializing...");
		initializeSystems();

		stop_watch.stop();
		const auto elapsed_time = stop_watch.getElapsedTime().count();
		ConsoleLogger::logInformation(k_engine_channel, "Initializing Done! took " + std::to_string(elapsed_time) + " ms");
	}

	void Application::update() noexcept
	{
		ConsoleLogger::logInformation(k_engine_channel, "Updating");
		auto frame_clock = Clock();

		is_running = true;
		frame_clock.start();
		while (is_running)
		{
			frame_clock.tick();
			updateSystems(frame_clock.getLastTickTime().count());
		}

		ConsoleLogger::logInformation(k_engine_channel, "Updating done! took " + std::to_string(frame_clock.getElapsedTime().count()) + " ms");
	}
	
	void Application::finalize() noexcept
	{
		ConsoleLogger::logInformation(k_engine_channel, "Finalizing");
		finalizeSystems();
	}

	void Application::configureSystems() noexcept
	{
		for (std::size_t i = 0; i != systems.size(); ++i)
		{
			systems[i]->configure(context.get());
		}
	}

	void Application::initializeSystems() noexcept
	{
		for (std::size_t i = 0; i != systems.size(); ++i)
		{
			systems[i]->initialize(context.get());
		}
	}
	
	void Application::updateSystems(const Float delta_time) noexcept
	{
		for (std::size_t i = 0; i != systems.size(); ++i)
		{
			systems[i]->update(context.get(), delta_time);
		}
	}
	
	void Application::finalizeSystems() noexcept
	{
		for (std::size_t i = 0; i != systems.size(); ++i)
		{
			systems[i]->finalize(context.get());
		}
	}
}
