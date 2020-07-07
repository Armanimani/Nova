#include "Engine/Systems/Exit/ExitSystem.hpp"
#include "Engine/Systems/Window/Event/window_events.hpp"

namespace nova
{
	void ExitSystem::configure([[maybe_unused]] Context* context) noexcept
	{
		
	}
	
	void ExitSystem::initialize([[maybe_unused]] Context* context) noexcept
	{
		
	}
	
	void ExitSystem::update(Context* context, [[maybe_unused]] Float delta_time) noexcept
	{
		processWindowCloseEvent(context);
	}
	
	void ExitSystem::finalize([[maybe_unused]] Context* context) noexcept
	{
		
	}

	void ExitSystem::processWindowCloseEvent(Context* context) noexcept
	{
		auto& event_manager = context->event_manager;
		if (event_manager.containEvent<WindowCloseEvent>())
		{
			context->is_running = false;
		}
	}
}
