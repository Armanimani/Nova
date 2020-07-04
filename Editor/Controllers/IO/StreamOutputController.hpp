#pragma once

#include <ostream>
#include <QtWidgets/QTextEdit>

namespace nova::editor
{
	class StreamOutputController final : public std::basic_streambuf<char>
	{
	public:
		StreamOutputController(std::ostream& stream, QTextEdit* text_edit);
		~StreamOutputController();

	protected:
		int_type overflow(int_type v) override;

		std::streamsize xsputn(const char* p, std::streamsize n) override;

	private:
		std::ostream& stream;
		std::streambuf* old_buffer;
		std::string string;

		QTextEdit* text_edit_widget;
	};
}
