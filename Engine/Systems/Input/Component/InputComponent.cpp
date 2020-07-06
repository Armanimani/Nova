#include "Engine/Systems/Input/Component/InputComponent.hpp"

namespace nova
{
	void InputComponent::update() noexcept
	{
		previous_key_state = current_key_state;
		
		previous_mouse_button_state = current_mouse_button_state;
		previous_mouse_position = current_mouse_position;
		previous_mouse_wheel_value = current_mouse_wheel_value;
	}

	void InputComponent::processEvent(const KeyDownEvent* registered_event, [[maybe_unused]] const Float delta_time) noexcept
	{
		current_key_state = current_key_state | registered_event->key;
	}

	void InputComponent::processEvent(const KeyUpEvent* registered_event, [[maybe_unused]] const Float delta_time) noexcept
	{
		current_key_state = current_key_state & !registered_event->key;
	}

	void InputComponent::processEvent(const MouseDownEvent* registered_event, [[maybe_unused]] const Float delta_time) noexcept
	{
		current_mouse_button_state = current_mouse_button_state | registered_event->button;
	}

	void InputComponent::processEvent(const MouseUpEvent* registered_event, [[maybe_unused]] const Float delta_time) noexcept
	{
		current_mouse_button_state = current_mouse_button_state & !registered_event->button;
	}

	void InputComponent::processEvent(const MouseWheelEvent* registered_event, [[maybe_unused]] const Float delta_time) noexcept
	{
		current_mouse_wheel_value = current_mouse_wheel_value + registered_event->increment;
	}

	void InputComponent::processEvent(const MouseMoveEvent* registered_event, [[maybe_unused]] const Float delta_time) noexcept
	{
		current_mouse_position = { registered_event->position_x, registered_event->position_y };
	}

	Bool InputComponent::isKeyDown(const KeyCode key_code) const noexcept
	{
		return !isKeyUp(key_code);
	} 
	
	Bool InputComponent::isKeyUp(const KeyCode key_code) const noexcept
	{
		return (current_key_state & key_code) == 0;
	}
	
	Bool InputComponent::wasKeyDown(const KeyCode key_code) const noexcept
	{
		return !wasKeyUp(key_code);
	}
	
	Bool InputComponent::wasKeyUp(const KeyCode key_code) const noexcept
	{
		return (previous_key_state & key_code) == 0;
	}
	
	Bool InputComponent::isMouseButtonDown(const MouseCode button_code) const noexcept
	{
		return isMouseButtonUp(button_code);
	}
	
	Bool InputComponent::isMouseButtonUp(const MouseCode button_code) const noexcept
	{
		return (current_mouse_button_state & button_code) == 0;
	}
	
	Bool InputComponent::wasMouseButtonDown(const MouseCode button_code) const noexcept
	{
		return !wasMouseButtonUp(button_code);
	}
	
	Bool InputComponent::wasMouseButtonUp(const MouseCode button_code) const noexcept
	{
		return (previous_mouse_button_state & button_code) == 0;
	}
	
	IntVector2 InputComponent::getMousePosition() const noexcept
	{
		return current_mouse_position;
	}
	
	IntVector2 InputComponent::getPreviousMousePosition() const noexcept
	{
		return previous_mouse_position;
	}
	
	InputComponent::MouseWheelValue InputComponent::getMouseWheelValue() const noexcept
	{
		return current_mouse_wheel_value;
	}
	
	InputComponent::MouseWheelValue InputComponent::getPreviousWheelValue() const noexcept
	{
		return previous_mouse_wheel_value;
	}
}
