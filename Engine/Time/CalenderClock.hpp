#pragma once

#include <chrono>

#include "Engine/Common/common.hpp"

namespace nova
{
	struct NOVA_API CalenderInformation
	{
		Int32 year{};
		Int32 moth{};
		Int32 day{};
		Int32 hour{};
		Int32 minute{};
		Int32 second{};
	};

	class NOVA_API CalenderClock
	{
	public:
		using clock_type = std::chrono::system_clock;
		
		static CalenderInformation getCalenderInformation() noexcept;
	};
}