#include "Engine/Systems/Window/WindowFactory.hpp"
#include "Engine/DesignPatterns/ServiceLocator.hpp"

namespace nova
{
	std::unique_ptr<IWindow> WindowFactory::create(const WindowSettings& settings) noexcept
	{
		return getAdapter()->createWindow(settings);
	}

	IWindowFactoryAdapter* WindowFactory::getAdapter()
	{
		return ServiceLocator<IWindowFactoryAdapter>::get();
	}
}
