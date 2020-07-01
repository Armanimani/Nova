#include "Engine/Systems/Window/Platform/Windows/Win32WindowFactoryAdapter.hpp"
#include "Engine/Systems/Window/Platform/Windows/Win32Window.hpp"

namespace nova
{
	std::unique_ptr<IWindow> Win32WindowFactoryAdapter::createWindow(const WindowSettings& settings) noexcept
	{
		return std::make_unique<Win32Window>(settings);
	}
}
