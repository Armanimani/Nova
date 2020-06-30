#pragma once

#include <chrono>

#include "Engine/Common/common.hpp"

namespace nova
{
	class NOVA_API Timer
	{
	public:
		using duration_type = std::chrono::duration<Float>;
		using clock_type = std::chrono::steady_clock;

		explicit Timer(std::chrono::seconds duration);
		explicit Timer(duration_type duration);

		void start() noexcept;

		[[nodiscard]] Bool isReady() const noexcept;
		[[nodiscard]] Bool isRunning() const noexcept;
		[[nodiscard]] duration_type getScheduledDuration() const noexcept;
		[[nodiscard]] duration_type getRemainingDuration() const noexcept;
	private:
		Bool is_running{ false };
		std::chrono::time_point<clock_type> start_time{};
		duration_type scheduled_duration{};
	};
}
