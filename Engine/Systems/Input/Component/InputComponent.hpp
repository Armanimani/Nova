#pragma once

#include "Engine/Common/common.hpp"
#include "Engine/Math/IntVector2.hpp"
#include "Engine/Systems/Input/Codes/KeyCode.hpp"
#include "Engine/Systems/Input/Codes/MouseCode.hpp"
#include "Engine/Systems/Input/Event/input_events.hpp"

namespace nova
{
	class NOVA_API InputComponent
	{
	public:
		using MouseWheelValue = Int32;

		void update() noexcept;
		
		void processEvent(const KeyDownEvent* registered_event, Float delta_time) noexcept;
		void processEvent(const KeyUpEvent* registered_event, Float delta_time) noexcept;

		void processEvent(const MouseDownEvent* registered_event, Float delta_time) noexcept;
		void processEvent(const MouseUpEvent* registered_event, Float delta_time) noexcept;
		void processEvent(const MouseWheelEvent* registered_event, Float delta_time) noexcept;
		void processEvent(const MouseMoveEvent* registered_event, Float delta_time) noexcept;
		
		[[nodiscard]] Bool isKeyDown(KeyCode key_code) const noexcept;
		[[nodiscard]] Bool isKeyUp(KeyCode key_code) const noexcept;
		[[nodiscard]] Bool wasKeyDown(KeyCode key_code) const noexcept;
		[[nodiscard]] Bool wasKeyUp(KeyCode key_code) const noexcept;

		[[nodiscard]] Bool isMouseButtonDown(MouseCode button_code) const noexcept;
		[[nodiscard]] Bool isMouseButtonUp(MouseCode button_code) const noexcept;
		[[nodiscard]] Bool wasMouseButtonDown(MouseCode button_code) const noexcept;
		[[nodiscard]] Bool wasMouseButtonUp(MouseCode button_code) const noexcept;

		[[nodiscard]] IntVector2 getMousePosition() const noexcept;
		[[nodiscard]] IntVector2 getPreviousMousePosition() const noexcept;
		[[nodiscard]] MouseWheelValue getMouseWheelValue() const noexcept;
		[[nodiscard]] MouseWheelValue getPreviousWheelValue() const noexcept;
	private:
		UInt32 current_key_state{};
		UInt32 current_mouse_button_state{};
		IntVector2 current_mouse_position{};
		MouseWheelValue current_mouse_wheel_value{};
		
		UInt32 previous_key_state{};
		UInt32 previous_mouse_button_state{};
		IntVector2 previous_mouse_position{};
		MouseWheelValue previous_mouse_wheel_value{};
	};
}
