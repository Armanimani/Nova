#pragma once

#include "Engine/Common/common.hpp"
namespace nova
{
	template <typename T>
	NOVA_API constexpr T max(const T lhs , const T rhs) noexcept
	{
		return (lhs > rhs) ? lhs : rhs;
	}

	template <typename T>
	NOVA_API constexpr T min(const T lhs, const T rhs) noexcept
	{
		return (lhs <= rhs) ? lhs : rhs;
	}
}
