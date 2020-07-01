#pragma once

#include "Engine/Systems/Window/IWindowFactoryAdapter.hpp"
#include "Engine/Common/common.hpp"

namespace nova
{
	class NOVA_API Win32WindowFactoryAdapter final: public IWindowFactoryAdapter
	{
	public:
		[[nodiscard]] std::unique_ptr<IWindow> createWindow(const WindowSettings& settings) noexcept override;
	};
}
