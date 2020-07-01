#pragma once

#include <memory>

#include "Engine/Common/common.hpp"
#include "Engine/Systems/Window/IWindow.hpp"
#include "Engine/Systems/Window/Settings/WindowSettings.hpp"

namespace nova
{
	class NOVA_API IWindowFactoryAdapter
	{
	public:
		virtual ~IWindowFactoryAdapter() = default;
		[[nodiscard]] virtual std::unique_ptr<IWindow> createWindow(const WindowSettings& settings) noexcept = 0;
	};
}