#pragma once

#include "Engine/Systems/ISystem.hpp"
#include "Engine/Systems/Input/Component/InputComponent.hpp"

namespace nova
{
	class NOVA_API InputSystem: public ISystem
	{
	public:
		void configure(Context* context) override;
		void initialize(Context* context) noexcept override;
		void update(Context* context, Float delta_time) noexcept override;
		void finalize(Context* context) noexcept override;
	private:
		template <typename EventType>
		static void processEvent(const EventManager& event_manager, InputComponent* input_component, Float delta_time);
		
		void processKeyEvents(const EventManager& event_manager, InputComponent* input_component, Float delta_time) const noexcept;
		void processMouseEvents(const EventManager& event_manager, InputComponent* input_component, Float delta_time) const noexcept;
	};

	
	template <typename EventType>
	void InputSystem::processEvent(const EventManager& event_manager, InputComponent* input_component, const Float delta_time)
	{
		event_manager.enumerateEvents<EventType>(
			[=](const EventType* registered_event)
			{
				input_component->processEvent(registered_event, delta_time);
			}
		);
	}
}
