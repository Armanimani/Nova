#include "Engine/Time/StopWatch.hpp"

#include <cassert>

namespace nova
{
	void StopWatch::start() noexcept
	{
		assert(!is_running);

		start_time = clock_type::now();
		is_running = true;
	}
	
	void StopWatch::stop() noexcept
	{
		assert(is_running);

		const auto now = clock_type::now();
		elapsed_duration += std::chrono::duration_cast<duration_type>(now - start_time);
		is_running = false;
	}
	
	void StopWatch::reset() noexcept
	{
		elapsed_duration = {};
		start_time = clock_type::now();
	}
	
	StopWatch::duration_type StopWatch::getElapsedTime() const noexcept
	{
		if (!is_running)
			return elapsed_duration;

		const auto now = clock_type::now();
		const auto current_duration = std::chrono::duration_cast<duration_type>(now - start_time);
		return elapsed_duration + current_duration;
	}
}
