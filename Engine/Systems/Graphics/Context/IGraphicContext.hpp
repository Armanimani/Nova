#pragma once

#include "Engine/Systems/Graphics/Context/IGraphicCommandContext.hpp"
#include "Engine/Application/Context.hpp"

namespace nova
{
	class NOVA_API IGraphicContext
	{
	public:
		virtual ~IGraphicContext() = default;
		
		virtual void initialize() noexcept = 0;
		virtual void update(Context* context, Float delta_time) noexcept = 0;
		virtual void present() noexcept = 0;
		virtual void finalize() noexcept = 0;
		
		virtual void handleWindowResizeEvent(UInt32 width, UInt32 height) noexcept = 0;
		
		virtual IGraphicCommandContext* getCommandContext() noexcept = 0;
	};
}
