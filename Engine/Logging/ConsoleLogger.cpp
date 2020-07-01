#include "Engine/Logging/ConsoleLogger.hpp"
#include "Engine/DesignPatterns/ServiceLocator.hpp"
#include <cassert>

namespace nova
{
	void ConsoleLogger::enableLoggingLevel(const LoggingLevel level)
	{
		s_logging_level |= static_cast<UInt8>(level);
	}
	void ConsoleLogger::disableLoggingLevel(const LoggingLevel level)
	{
		s_logging_level &= ~static_cast<UInt8>(level);
	}

	bool ConsoleLogger::isLoggingLevelEnabled(const LoggingLevel level)
	{
		return s_logging_level & static_cast<UInt8>(level);
	}

	void ConsoleLogger::logCritical(const std::string_view channel, const std::string_view log_message) noexcept
	{
		if (!isLoggingLevelEnabled(LoggingLevel::critical))
			return;

		getAdapter()->logCritical (channel, log_message);
	}
	
	void ConsoleLogger::logWarning(const std::string_view channel, const std::string_view log_message) noexcept
	{
		if (!isLoggingLevelEnabled(LoggingLevel::warning))
			return;

		getAdapter()->logWarning(channel, log_message);
	}
	
	void ConsoleLogger::logInformation(const std::string_view channel, const std::string_view log_message) noexcept
	{
		if (!isLoggingLevelEnabled(LoggingLevel::information))
			return;

		getAdapter()->logInformation(channel, log_message);
	}
	
	void ConsoleLogger::logDebug(const std::string_view channel, const std::string_view log_message) noexcept
	{
		if (!isLoggingLevelEnabled(LoggingLevel::debug))
			return;

		getAdapter()->logDebug(channel, log_message);
	}
	
	IConsoleLoggerAdapter* ConsoleLogger::getAdapter()
	{
		const auto adapter = ServiceLocator<IConsoleLoggerAdapter>::get();
		
		assert(adapter);

		return adapter;
	}
}
