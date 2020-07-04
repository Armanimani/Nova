#pragma once

#include<QtCore/QFile>
#include <unordered_map>

#include "Editor/constants.hpp"

namespace nova::editor
{
	enum class StyleSheetType
	{
		dark
	};

	class StyleSheetManager
	{
	public:
		static QString getStylesheet(StyleSheetType type);
	private:
		static std::unordered_map<StyleSheetType, QString> registry;
	};

	inline QString StyleSheetManager::getStylesheet(const StyleSheetType type)
	{
		QFile style_file(registry[type]);
		style_file.open(QFile::ReadOnly);

		return QString(style_file.readAll());
	}

	std::unordered_map<StyleSheetType, QString> StyleSheetManager::registry =
	{
		{StyleSheetType::dark, k_stylesheet_dark}
	};
}