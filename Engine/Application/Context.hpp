#pragma once

#include "Engine/Common/common.hpp"
#include "Engine/Entity/entity.hpp"
#include "Engine/Event/EventManager.hpp"

namespace nova
{
	struct NOVA_API Context
	{
		Context()
		{
			master_entity = entity_manager.create();
		}

		Bool is_running{ false };
		EntityManager entity_manager{};
		Entity master_entity{};
		
		EventManager event_manager{};
	};
}
