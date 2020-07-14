#include "Engine/Systems/Graphics/GraphicSystem.hpp"
#include "Engine/Systems/Graphics/Components/GraphicComponent.hpp"
#include "Engine/Systems/Graphics/Context/GraphicContextFactory.hpp"
#include "Engine/Systems/Graphics/Settings/GraphicSettings.hpp"
#include "Engine/Systems/Graphics/Renderer/BaseRenderer.hpp"
#include "Engine/Systems/Window/Components/WindowComponent.hpp"
#include "Engine/Systems/Window/Event/WindowResizeEvent.hpp"

namespace nova
{
	void GraphicSystem::configure([[maybe_unused]] Context* context) noexcept {}

	void GraphicSystem::initialize(Context* context) noexcept
	{
		const auto settings = context->entity_manager.get<GraphicSettings>(context->master_entity);
		const auto window_handle = context->entity_manager.get<WindowComponent>(context->master_entity).window_handle;
		graphic_context = GraphicContextFactory::create(settings, window_handle);		
		graphic_context->initialize();

		registerRenderer();
		const auto graphic_command_context = graphic_context->getCommandContext();
		initializeRendererList(graphic_command_context);
	}

	
	void GraphicSystem::update(Context* context, const Float delta_time) noexcept
	{
		graphic_context->update(context, delta_time);
		
		const auto& event_manager = context->event_manager;
		processResizeEvent(event_manager);
		
		updateRendererList(context, delta_time);
		
		graphic_context->present();
	}
	
	void GraphicSystem::finalize([[maybe_unused]] Context* context) noexcept
	{
		finalizeRendererList();
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

	void GraphicSystem::registerRenderer() noexcept
	{
		renderer_list.push_back(std::make_unique<BaseRenderer>());
	}

	void GraphicSystem::initializeRendererList(IGraphicCommandContext* command_context) noexcept
	{
		for (UInt32 i = 0; i != renderer_list.size(); ++i)
			renderer_list[i]->initialize(command_context);
	}
	
	void GraphicSystem::updateRendererList(Context* context, const Float delta_time) noexcept
	{
		for (UInt32 i = 0; i != renderer_list.size(); ++i)
			renderer_list[i]->update(context, delta_time);
	}
	
	void GraphicSystem::finalizeRendererList() noexcept
	{
		for (UInt32 i = 0; i != renderer_list.size(); ++i)
			renderer_list[i]->finalize();
	}

	void GraphicSystem::processResizeEvent(const EventManager& event_manager) noexcept
	{
		event_manager.enumerateEvents<WindowResizeEvent>(
			[=](const WindowResizeEvent* registered_event)
			{
				const auto width = registered_event->width;
				const auto height = registered_event->height;
				graphic_context->handleWindowResizeEvent(width, height);
			}
		);
	}
}
