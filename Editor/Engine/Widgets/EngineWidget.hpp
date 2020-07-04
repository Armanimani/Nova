#pragma once

#include <QtWidgets/QtWidgets>

namespace nova::editor
{
	class EngineWidget final : public QWidget
	{
		Q_OBJECT
	public:
		explicit EngineWidget(QWidget* parent);

		[[nodiscard]] WId getWindowHandle() const noexcept;
	protected:
		QPaintEngine* paintEngine() const override;
	};
}