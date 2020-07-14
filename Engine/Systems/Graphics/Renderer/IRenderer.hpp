#pragma once

#include "Engine/Common/common.hpp"
#include "Engine/Application/Context.hpp"
#include "Engine/Systems/Graphics/Context/IGraphicCommandContext.hpp"

namespace nova
{
	class NOVA_API IRenderer
	{
	public:
		virtual void initialize(IGraphicCommandContext* command_context) noexcept = 0;
		virtual void update(Context* context, Float delta_time) noexcept = 0;
		virtual void finalize() noexcept = 0;
	};
}