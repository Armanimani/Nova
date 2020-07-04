#include "Editor/EditorWindow.hpp"

#include <iostream>
#include <QtWidgets/QScrollBar>

#include "Editor/constants.hpp"
#include "Editor/StyleSheet/StyleSheetManager.hpp"

namespace nova::editor
{
	EditorWindow::EditorWindow(QWidget* parent)
		: QMainWindow(parent)
	{
		this->setStyleSheet(StyleSheetManager::getStylesheet(StyleSheetType::dark));

		ui.setupUi(this);

		this->setWindowIcon(QIcon(k_icon_nova_logo_black_32));

		redirectStreamOutput();
		connectSignalAndSlots();
	}

	void EditorWindow::showEvent(QShowEvent* event)
	{
		initializeEngineApplication();
	}

	void EditorWindow::closeEvent(QCloseEvent* event)
	{
		// Ensure the std::cout is piped back to console
		output_controller.reset();
		engine_application.reset();
	}

	void EditorWindow::onTextEditOutputTextChanged() const
	{
		auto vertical_scroll_bar = static_cast<QScrollBar*>(ui.text_edit_debug->verticalScrollBar());
		vertical_scroll_bar->setValue(vertical_scroll_bar->maximum());
	}

	void EditorWindow::connectSignalAndSlots() const
	{
		connect(ui.action_exit, &QAction::triggered, this, &QMainWindow::close);
		connect(ui.text_edit_debug, &QTextEdit::textChanged, this, &EditorWindow::onTextEditOutputTextChanged);
	}

	void EditorWindow::redirectStreamOutput()
	{
		output_controller = std::make_unique<StreamOutputController>(std::cout, ui.text_edit_debug);
	}

	void EditorWindow::initializeEngineApplication()
	{
		EngineSettings settings;
		settings.graphic_api = GraphicApi::direct_x12;
		settings.window_handle = reinterpret_cast<void*>(ui.widget_engine->getWindowHandle());
		engine_application = std::make_unique<EngineApplication>(settings);
		engine_application->start();
	}
}