#include "Engine/Time/CalenderClock.hpp"

namespace nova
{
	constexpr auto k_base_year = 1900;
	
	CalenderInformation CalenderClock::getCalenderInformation() noexcept
	{
		const auto now = clock_type::to_time_t(clock_type::now());

		tm time_structure{};
		localtime_s(&time_structure, &now);
		
		const auto year = time_structure.tm_year + k_base_year;
		const auto month = time_structure.tm_mon;
		const auto day = time_structure.tm_mday;
		const auto hour = time_structure.tm_hour;
		const auto minute = time_structure.tm_min;
		const auto second = time_structure.tm_sec;

		return { year, month, day, hour, minute, second };
	}

}
