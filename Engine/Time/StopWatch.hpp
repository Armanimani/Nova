#pragma once

#include <chrono>

#include "Engine/Common/common.hpp"

namespace nova
{
	class NOVA_API StopWatch
	{
	public:
		using duration_type = std::chrono::duration<Float>;
		using clock_type = std::chrono::steady_clock;

		void start() noexcept;
		void stop() noexcept;
		void reset() noexcept;

		[[nodiscard]] duration_type getElapsedTime() const noexcept;
	private:
		Bool is_running{ false };
		std::chrono::time_point<clock_type> start_time{};
		duration_type elapsed_duration{};
	};
}
