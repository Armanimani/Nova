#pragma once

#include "Engine/Systems//ISystem.hpp"
#include "Engine/Common/common.hpp"

namespace nova
{
	class NOVA_API ExitSystem final: public ISystem
	{
	public:
		void configure(Context * context) noexcept override;
		void initialize(Context* context) noexcept override;
		void update(Context* context, Float delta_time) noexcept override;
		void finalize(Context* context) noexcept override;
	private:
		static void processWindowCloseEvent(Context* context) noexcept;
	};
}
