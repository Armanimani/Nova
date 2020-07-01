#include "Engine/Systems/Graphics/GraphicSystem.hpp"
#include "Engine/Systems/Graphics/Components/GraphicComponent.hpp"
#include "Engine/Systems/Graphics/Context/GraphicContextFactory.hpp"
#include "Engine/Systems/Graphics/Settings/GraphicSettings.hpp"
#include "Engine/Systems/Window/Components/WindowComponent.hpp"

namespace nova
{
	void GraphicSystem::configure([[maybe_unused]] Context* context) noexcept {}

	void GraphicSystem::initialize(Context* context) noexcept
	{
		const auto settings = context->entity_manager.get<GraphicSettings>(context->master_entity);
		const auto window_handle = context->entity_manager.get<WindowComponent>(context->master_entity).window_handle;
		graphic_context = GraphicContextFactory::create(settings, window_handle);		
		graphic_context->initialize();
	}

	
	void GraphicSystem::update([[maybe_unused]] Context* context, [[maybe_unused]] Float delta_time) noexcept
	{
		graphic_context->present();
	}
	
	void GraphicSystem::finalize([[maybe_unused]] Context* context) noexcept
	{
		graphic_context->finalize();
	}

	void GraphicSystem::initializeComponent(Context* context) noexcept
	{
		context->entity_manager.reserve<GraphicComponent>(1);
		context->entity_manager.emplace<GraphicComponent>(context->master_entity);

		auto& component = context->entity_manager.get<GraphicComponent>(context->master_entity);
		const auto settings = context->entity_manager.get<GraphicSettings>(context->master_entity);
		component.is_v_sync_on = settings.is_v_sync_enabled;
	}
}
