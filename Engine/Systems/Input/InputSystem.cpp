#include "Engine/Systems/Input/InputSystem.hpp"
#include "Engine/Systems/Input/Component/InputComponent.hpp"
#include "Engine/Systems/Input/Event/input_events.hpp"
#include "Engine/Logging/ConsoleLogger.hpp"

namespace nova
{
	void InputSystem::configure([[maybe_unused]] Context* context)
	{
		
	}
	
	void InputSystem::initialize([[maybe_unused]] Context* context) noexcept
	{
		context->entity_manager.reserve<InputComponent>(1);
		context->entity_manager.emplace<InputComponent>(context->master_entity);
	}
	
	void InputSystem::update(Context* context, const Float delta_time) noexcept
	{
		const auto& event_manager = context->event_manager;
		auto input_component = &context->entity_manager.get<InputComponent>(context->master_entity);

		input_component->update();
		processKeyEvents(event_manager, input_component, delta_time);
		processMouseEvents(event_manager, input_component, delta_time);
	}
	
	void InputSystem::finalize([[maybe_unused]] Context* context) noexcept
	{
		
	}

	void InputSystem::processKeyEvents(const EventManager& event_manager, InputComponent* input_component, const Float delta_time) const noexcept
	{
		processEvent<KeyDownEvent>(event_manager, input_component, delta_time);
		processEvent<KeyUpEvent>(event_manager, input_component, delta_time);
	}


	void InputSystem::processMouseEvents(const EventManager& event_manager, InputComponent* input_component, const Float delta_time) const noexcept
	{
		processEvent<MouseDownEvent>(event_manager, input_component, delta_time);
		processEvent<MouseUpEvent>(event_manager, input_component, delta_time);
		processEvent<MouseWheelEvent>(event_manager, input_component, delta_time);
		processEvent<MouseMoveEvent>(event_manager, input_component, delta_time);
	}
}
