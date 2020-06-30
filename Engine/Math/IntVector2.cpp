#include "Engine/Math/IntVector2.hpp"
#include "Engine/Math/utilities.hpp"

#include <algorithm>
#include <cassert>

namespace nova
{
	constexpr Int32 k_min_index = 0;
	constexpr Int32 k_max_index = 1;

	
	const IntVector2 IntVector2::k_zero{0, 0};
	const IntVector2 IntVector2::k_unit_x{1, 0};
	const IntVector2 IntVector2::k_unit_y{0, 1};

	
	IntVector2::IntVector2(const Int32 uniform_value)
		: x{ uniform_value }, y{uniform_value} {}

	IntVector2::IntVector2(const Int32 x_value, const Int32 y_value)
		: x{ x_value }, y{ y_value } {}

	const Int32& IntVector2::operator()(const Int32 index) const noexcept
	{
		assert(index >= k_min_index && index <= k_max_index);
		
		return (&x)[index];
	}
	
	Int32& IntVector2::operator()(const Int32 index) noexcept
	{
		assert(index >= k_min_index && index <= k_max_index);
		
		return (&x)[index];
	}
	
	const Int32& IntVector2::operator[](const Int32 index) const noexcept
	{
		assert(index >= k_min_index && index <= k_max_index);
		
		return (&x)[index];
	}
	Int32& IntVector2::operator[](const Int32 index) noexcept
	{
		assert(index >= k_min_index && index <= k_max_index);
		
		return (&x)[index];
	}

	Bool IntVector2::operator==(const IntVector2& other) const noexcept
	{
		return (x == other.x) && (y == other.y);
	}
	
	Bool IntVector2::operator!=(const IntVector2& other) const noexcept
	{
		return !((*this) == other);
	}

	IntVector2& IntVector2::operator+=(const IntVector2& other) noexcept
	{
		x += other.x;
		y += other.y;

		return *this;
	}
	
	IntVector2& IntVector2::operator-=(const IntVector2& other) noexcept
	{
		x -= other.x;
		y -= other.y;

		return *this;
	}
	
	IntVector2& IntVector2::operator*=(const Int32 value) noexcept
	{
		x *= value;
		y *= value;

		return *this;
	}
	

	Int32 IntVector2::getMax() const noexcept
	{
		return max(x, y);
	}
	
	Int32 IntVector2::getMin() const noexcept
	{
		return min(x, y);
	}
	
	Float IntVector2::getLength() const noexcept
	{
		return sqrtf(static_cast<Float>(getLengthSquared()));
	}
	
	Int32 IntVector2::getLengthSquared() const noexcept
	{
		return x * x + y * y;
	}
	
	IntVector2 operator+(const IntVector2& lhs, const IntVector2& rhs) noexcept
	{
		return { lhs.x + rhs.x, lhs.y + rhs.y };
	}
	
	IntVector2 operator-(const IntVector2& lhs, const IntVector2& rhs) noexcept
	{
		return { lhs.x - rhs.x, lhs.y - rhs.y };
	}

	IntVector2 operator*(const IntVector2& vector, const Int32 scale) noexcept
	{
		return { vector.x * scale, vector.y * scale };
	}

	IntVector2 operator*(const Int32 scale, const IntVector2& vector) noexcept
	{
		return { scale * vector.x, scale * vector.y };
	}
}
