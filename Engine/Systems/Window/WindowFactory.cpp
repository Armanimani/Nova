#include "Engine/Systems/Window/WindowFactory.hpp"
#include "Engine/DesignPatterns/ServiceLocator.hpp"

namespace nova
{
	std::unique_ptr<IWindow> WindowFactory::create(const WindowSettings& settings, EventManager* event_manager) noexcept
	{
		return getAdapter()->createWindow(settings, event_manager);
	}

	IWindowFactoryAdapter* WindowFactory::getAdapter()
	{
		return ServiceLocator<IWindowFactoryAdapter>::get();
	}
}
