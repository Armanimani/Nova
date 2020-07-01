#pragma once

#include "Engine/Systems/ISystem.hpp"
#include "Engine/Systems/Window/IWindow.hpp"
#include "Engine/Common/common.hpp"

#include <memory>

namespace nova
{
	class NOVA_API WindowSystem final: public ISystem
	{
	public:
		void configure(Context* context) noexcept override;
		void initialize(Context* context) noexcept override;
		void update(Context* context, Float delta_time) noexcept override;
		void finalize(Context* context) noexcept override;
	private:
		std::unique_ptr<IWindow> window{ nullptr };
	};
}