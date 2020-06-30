#pragma once

#pragma warning(disable: 4003) 
#include <entt/entity/registry.hpp>
#pragma warning(default: 4003) 

namespace nova
{
	using EntityManager = entt::registry;
	using Entity = entt::entity;
}
