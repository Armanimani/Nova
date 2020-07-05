#include "Engine/Event/EventSpecification.hpp"

namespace nova
{
	EventSpecification::EventSpecification(EventSpecification&& other) noexcept
	{
		event_type_id = other.event_type_id;
		std::swap(registered_event, other.registered_event);
	}
	
	EventSpecification& EventSpecification::operator=(EventSpecification&& other) noexcept
	{
		event_type_id = other.event_type_id;
		std::swap(registered_event, other.registered_event);
		return *this;
	}
}
