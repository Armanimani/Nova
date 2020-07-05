#include "Engine/Systems/Input/InputSystem.hpp"
#include "Engine/Systems/Input/Component/InputComponent.hpp"

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
	
	void InputSystem::update([[maybe_unused]] Context* context, [[maybe_unused]] Float delta_time) noexcept
	{
		
	}
	
	void InputSystem::finalize([[maybe_unused]] Context* context) noexcept
	{
		
	}
}
