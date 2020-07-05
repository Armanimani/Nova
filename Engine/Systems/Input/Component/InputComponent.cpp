#include "Engine/Systems/Input/Component/InputComponent.hpp"

namespace nova
{
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
