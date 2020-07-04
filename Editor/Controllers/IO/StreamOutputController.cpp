#include "Editor/Controllers/IO/StreamOutputController.hpp"

namespace nova::editor
{
	StreamOutputController::StreamOutputController(std::ostream& stream, QTextEdit* text_edit)
		: stream(stream)
	{
		text_edit_widget = text_edit;
		old_buffer = stream.rdbuf();
		stream.rdbuf(this);
	}

	StreamOutputController::~StreamOutputController()
	{
		if (!string.empty())
			text_edit_widget->append(string.c_str());

		stream.rdbuf(old_buffer);
	}

	std::basic_streambuf<char>::int_type StreamOutputController::overflow(int_type v)
	{
		if (v == '\n')
		{
			text_edit_widget->append(string.c_str());
			string.erase(string.begin(), string.end());
		}
		else
			string += v;

		return v;
	}

	std::streamsize StreamOutputController::xsputn(const char* p, std::streamsize n)
	{
		string.append(p, p + n);

		int pos = 0;
		while (pos != std::string::npos)
		{
			pos = string.find('\n');
			if (pos != std::string::npos)
			{
				std::string tmp(string.begin(), string.begin() + pos);
				text_edit_widget->append(tmp.c_str());
				string.erase(string.begin(), string.begin() + pos + 1);
			}
		}

		return n;
	}
}