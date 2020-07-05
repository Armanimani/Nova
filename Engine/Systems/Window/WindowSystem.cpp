#include "Engine/Systems/Window/WindowSystem.hpp"
#include "Engine/Systems/Window/WindowFactory.hpp"
#include "Engine/Systems/Window/Components/WindowComponent.hpp"
#include "Engine/Systems/Window/Settings/WindowSettings.hpp"
#include "Engine/DesignPatterns/ServiceLocator.hpp"
#include "Engine/Logging/Implementation/spdlog/ConsoleLoggerAdapter_SpdLog.hpp"
#include "IWindowFactoryAdapter.hpp"

#ifdef _WIN32
	#include "Engine/Systems/Window/Platform/Windows/Win32WindowFactoryAdapter.hpp"
#else
	#pragma error "Window system only supports windows platform for now!"
#endif

namespace nova
{
	void WindowSystem::configure([[maybe_unused]] Context* context) noexcept
	{
	#ifdef WIN32
		auto window_factory = std::make_unique<Win32WindowFactoryAdapter>();
		ServiceLocator<IWindowFactoryAdapter>::provide(std::move(window_factory));
	#else
		#pragma error "Window system only supports windows platform for now!"
	#endif
	}

	void WindowSystem::initialize(Context* context) noexcept
	{
		const auto settings = context->entity_manager.get<WindowSettings>(context->master_entity);
		void* handle = settings.custom_window_handle;
		auto own_window = false;
		if (!handle)
		{
			window = WindowFactory::create(settings, &context->event_manager);
			handle = window->getHandle();
			own_window = true;
		}
		
		context->entity_manager.reserve<WindowComponent>(1);	
		context->entity_manager.emplace<WindowComponent>(context->master_entity, own_window, handle);

		if (window)
			window->show();
	}
	
	void WindowSystem::update([[maybe_unused]] Context* context, [[maybe_unused]] Float delta_time) noexcept
	{
		// TODO: The logic for updating the window can be decoupled form the main thread
		if (window)
			window->update();
	}

	void WindowSystem::finalize([[maybe_unused]] Context* context) noexcept
	{
		if (window->isVisible())
			window->close();
	}
}
