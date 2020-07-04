#pragma once

#include "ui_EditorWindow.h"

#include <memory>

#include "Controllers/IO/StreamOutputController.hpp"
#include "Editor/Engine/Applications/EngineApplication.hpp"


namespace nova::editor
{
	class EditorWindow : public QMainWindow
	{
		Q_OBJECT

	public:
		EditorWindow(QWidget* parent = Q_NULLPTR);
	protected:
		void showEvent(QShowEvent* event) override;
		void closeEvent(QCloseEvent* event) override;
	private slots:
		void onTextEditOutputTextChanged() const;
	private:
		Ui::EditorWindowClass ui;

		std::unique_ptr<StreamOutputController> output_controller{};
		std::unique_ptr<EngineApplication> engine_application{};

		void connectSignalAndSlots() const;
		void redirectStreamOutput();
		void initializeEngineApplication();
	};
}