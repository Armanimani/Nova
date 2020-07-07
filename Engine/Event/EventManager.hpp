#pragma once

#include "Engine/Common/common.hpp"
#include "Engine/Types/TypeIdentifier.hpp"
#include "Engine/Event/EventSpecification.hpp"

#include <vector>

namespace nova
{
	constexpr auto k_default_event_buffer_size = 100;
	
	class NOVA_API EventManager
	{
	public:
		using EventTypeID = UInt32;

		EventManager() = default;
		EventManager(const EventManager& other) = delete;
		EventManager(EventManager&& other) noexcept = delete;
		EventManager& operator=(const EventManager& other) = delete;
		EventManager& operator=(EventManager&& other) noexcept = delete;
		~EventManager() = default;
		
		void clear() noexcept;
		
		template<typename EventType>
		void addEvent(std::unique_ptr<IEvent>&& new_event) noexcept;

		template<typename EventType, typename VisitorFunc>
		void enumerateEvents(VisitorFunc&& visitor_function) const noexcept;

		template<typename EventType>
		Bool containEvent() const noexcept;
	private:
		std::vector<EventSpecification> event_registry;

		template<typename EventType>
		static EventTypeID getEventTypeId() noexcept;
	};

	
	inline void EventManager::clear() noexcept
	{
		event_registry.clear();
		event_registry.reserve(k_default_event_buffer_size);
	}

	template <typename EventType>
	void EventManager::addEvent(std::unique_ptr<IEvent>&& new_event) noexcept
	{
		const auto event_type_id = getEventTypeId<EventType>();
		event_registry.emplace_back(event_type_id, std::move(new_event));
	}

	template <typename EventType, typename VisitorFunc>
	void EventManager::enumerateEvents(VisitorFunc&& visitor_function) const noexcept
	{
		const auto event_type_id = getEventTypeId<EventType>();
	
		for (auto& event_specification: event_registry)
		{
			if (event_specification.event_type_id != event_type_id)
				continue;
			
			const auto registered_event = static_cast<EventType*>(event_specification.registered_event.get());
			visitor_function(registered_event);
		}
	}

	template <typename EventType>
	Bool EventManager::containEvent() const noexcept
	{
		const auto event_type_id = getEventTypeId<EventType>();

		for (auto& event_specification : event_registry)
		{
			if (event_specification.event_type_id == event_type_id)
			{
				return true;
			}
		}
		return false;
	}

	template <typename EventType>
	EventManager::EventTypeID EventManager::getEventTypeId() noexcept
	{
		return TypeIdentifier::get<EventType>();
	}
}
