#pragma once

#include <memory>

#include "Engine/Systems/Window/IWindow.hpp"
#include "Engine/Systems/Window/Settings/WindowSettings.hpp"
#include "Engine/Systems/Window/IWindowFactoryAdapter.hpp"
#include "Engine/Common/common.hpp"

namespace nova
{
	class NOVA_API WindowFactory
	{
	public:
		static std::unique_ptr<IWindow> create(const WindowSettings& settings, EventManager* event_manager) noexcept;

	private:
		static IWindowFactoryAdapter* getAdapter();
	};
}
