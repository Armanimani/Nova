#include "Editor/Engine/Widgets/EngineWidget.hpp"

namespace nova::editor
{
	EngineWidget::EngineWidget(QWidget* parent)
		: QWidget(parent) {}

	WId EngineWidget::getWindowHandle() const noexcept
	{
		return winId();
	}

	QPaintEngine* EngineWidget::paintEngine() const
	{
		// TODO: This need to be overwritten if context is DirectX otherwise it need to be here for OpenGL
		return nullptr;
	}
}
