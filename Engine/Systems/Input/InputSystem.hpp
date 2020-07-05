#pragma once

#include "Engine/Systems/ISystem.hpp"

namespace nova
{
	class NOVA_API InputSystem: public ISystem
	{
	public:
		void configure(Context* context) override;
		void initialize(Context* context) noexcept override;
		void update(Context* context, Float delta_time) noexcept override;
		void finalize(Context* context) noexcept override;
	};
}
