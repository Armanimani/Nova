#pragma once

#include "Engine/Types/base_types.hpp"
#include "Engine/Logging/IConsoleLoggerAdapter.hpp"
#include <spdlog/spdlog.h>


namespace nova
{
	class ConsoleLoggerAdapter_SpdLog final: public IConsoleLoggerAdapter
	{
	public:
		ConsoleLoggerAdapter_SpdLog();
		
		void logCritical(std::string_view channel, std::string_view log_message) noexcept override;
		void logWarning(std::string_view channel, std::string_view log_message) noexcept override;
		void logInformation(std::string_view channel, std::string_view log_message) noexcept override;
		void logDebug(std::string_view channel, std::string_view log_message) noexcept override;
	private:	
		[[nodiscard]] static spdlog::logger* createLogger(std::string_view channel) noexcept;
		[[nodiscard]] spdlog::logger* getLogger(std::string_view channel) noexcept;
	};
}
