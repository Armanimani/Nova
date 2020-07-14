#include "Engine/Systems/Graphics/Renderer/BaseRenderer.hpp"

namespace nova
{
	void BaseRenderer::initialize(IGraphicCommandContext* command_context) noexcept
	{
		this->command_context = command_context;
	}
	
	void BaseRenderer::update(Context* context, const Float delta_time) noexcept
	{
		command_context->clearRenderTargetViewColor(0.0f, 0.2f, 0.4f, 1.0f);
	}
	
	void BaseRenderer::finalize() noexcept
	{
		
	}
}
