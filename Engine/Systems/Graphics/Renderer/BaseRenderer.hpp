#pragma once

#include "Engine/Systems/Graphics/Renderer/IRenderer.hpp"

namespace nova
{
	class NOVA_API BaseRenderer : public IRenderer
	{
	public:
		void initialize(IGraphicCommandContext* command_context) noexcept override;
		void update(Context* context, Float delta_time) noexcept override;
		void finalize() noexcept override;
	private:
		IGraphicCommandContext* command_context{ nullptr };
	};
}
