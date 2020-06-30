#include "Engine/Time/Timer.hpp"

#include <cassert>

namespace nova
{
	Timer::Timer(const std::chrono::seconds duration)
		: scheduled_duration{ std::chrono::duration_cast<duration_type>(duration) } {}
	
	Timer::Timer(const duration_type duration)
		: scheduled_duration{ duration } {}

	void Timer::start() noexcept
	{
		start_time = clock_type::now();
		is_running = true;
	}
	
	Bool Timer::isReady() const noexcept
	{
		assert(is_running);

		const auto now = clock_type::now();
		return ((now - start_time) > scheduled_duration);
	}
	
	Bool Timer::isRunning() const noexcept
	{
		return is_running;
	}
	
	Timer::duration_type Timer::getScheduledDuration() const noexcept
	{
		return scheduled_duration;
	}
	
	Timer::duration_type Timer::getRemainingDuration() const noexcept
	{
		if (!is_running)
			return scheduled_duration;

		const auto now = clock_type::now();
		const auto remaining_duration = scheduled_duration - (now - start_time);

		if (remaining_duration.count() < 0)
			return {};

		return std::chrono::duration_cast<duration_type>(remaining_duration);
	}
}
