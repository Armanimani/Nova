#pragma once

#include "Engine/Common/common.hpp"
#include "Engine/Entity/entity.hpp"

namespace nova
{
	struct NOVA_API Context
	{
		Context()
		{
			master_entity = entity_manager.create();
		}

		EntityManager entity_manager{};
		Entity master_entity{};
	};
}
