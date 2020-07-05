#pragma once

#include "Engine/Common/common.hpp"
#include "Engine/Event/IEvent.hpp"

#include <memory>


namespace nova
{
	struct NOVA_API EventSpecification
	{
		EventSpecification(const UInt32 event_type_id, std::unique_ptr<IEvent>&& registered_event)
			: event_type_id{ event_type_id }, registered_event{ std::move(registered_event) }{}

		EventSpecification(EventSpecification&& other) noexcept;
		EventSpecification& operator=(EventSpecification&& other) noexcept;
		
		UInt32 event_type_id{ 0 };
		std::unique_ptr<IEvent> registered_event{ nullptr };
	};
}
