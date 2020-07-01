#pragma once

#include "Engine/Common/common.hpp"

namespace nova
{
	class NOVA_API IWindow
	{
	public:
		virtual ~IWindow() = default;

		[[nodiscard]] virtual void* getHandle() const noexcept = 0;

		virtual void update() const noexcept = 0;
		virtual void close() const noexcept = 0;
		
		virtual void focus() const noexcept = 0;
		virtual void show() const noexcept = 0;
		virtual void hide() const noexcept = 0;
		
		virtual void maximize() const noexcept = 0;
		virtual void minimize() const noexcept = 0;
		virtual void restore() const noexcept = 0;

		[[nodiscard]] virtual Bool isMaximized() const noexcept = 0;
		[[nodiscard]] virtual Bool isMinimized() const noexcept = 0;
		[[nodiscard]] virtual Bool isVisible() const noexcept = 0;
		[[nodiscard]] virtual Bool isFocused() const noexcept = 0;
		
		virtual void setSize(Int32 x, Int32 y, Int32 width, Int32 height) const noexcept = 0;

		[[nodiscard]] virtual Int32 getWidth() const noexcept = 0;
		[[nodiscard]] virtual Int32 getHeight() const noexcept = 0;
	};
}
