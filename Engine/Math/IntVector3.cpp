#include "Engine/Math/IntVector3.hpp"
#include "Engine/Math/utilities.hpp"

#include <cassert>

namespace nova
{
	constexpr Int32 k_min_index = 0;
	constexpr Int32 k_max_index = 2;
	
	
	const IntVector3 IntVector3::k_zero{ 0, 0, 0 };
	const IntVector3 IntVector3::k_unit_x{ 1, 0, 0 };
	const IntVector3 IntVector3::k_unit_y{ 0, 1, 0 };
	const IntVector3 IntVector3::k_unit_z{ 0, 0, 1 };
	const IntVector3 IntVector3::k_up{ 0, 0, 1 };
	const IntVector3 IntVector3::k_down{ 0, 0, -1 };
	const IntVector3 IntVector3::k_right{ 0, 1, 0 };
	const IntVector3 IntVector3::k_left{ 0, -1, 0 };
	const IntVector3 IntVector3::k_forward{ 1, 0, 0 };
	const IntVector3 IntVector3::k_backward{ -1, 0, 0 };

	
	IntVector3::IntVector3(const Int32 uniform_value)
		: x{ uniform_value }, y{ uniform_value }, z{ uniform_value }{}

	IntVector3::IntVector3(const Int32 x_value, const Int32 y_value, const Int32 z_value)
		: x{ x_value }, y{ y_value }, z{ z_value }{}

	IntVector3::IntVector3(const IntVector2& vector)
		: x{ vector.x }, y{ vector.y }{}

	const Int32& IntVector3::operator()(const Int32 index) const noexcept
	{
		assert(index >= k_min_index && index <= k_max_index);

		return (&x)[index];
	}
	
	Int32& IntVector3::operator()(const Int32 index) noexcept
	{
		assert(index >= k_min_index && index <= k_max_index);

		return (&x)[index];
	}
	
	const Int32& IntVector3::operator[](const Int32 index) const noexcept
	{
		assert(index >= k_min_index && index <= k_max_index);

		return (&x)[index];
	}
	
	Int32& IntVector3::operator[](const Int32 index) noexcept
	{
		assert(index >= k_min_index && index <= k_max_index);

		return (&x)[index];
	}
	
	Bool IntVector3::operator==(const IntVector3& other) const noexcept
	{
		return (x == other.x) && (y == other.y) && (z == other.z);
	}
	
	Bool IntVector3::operator!=(const IntVector3& other) const noexcept
	{
		return !((*this) == other);
	}
	
	IntVector3& IntVector3::operator+=(const IntVector3& other) noexcept
	{
		x += other.x;
		y += other.y;
		z += other.z;

		return *this;
	}
	
	IntVector3& IntVector3::operator-=(const IntVector3& other) noexcept
	{
		x -= other.x;
		y -= other.y;
		z -= other.z;

		return *this;
	}
	
	IntVector3& IntVector3::operator*=(const Int32 value) noexcept
	{
		x *= value;
		y *= value;
		z *= value;

		return *this;
	}
	
	Int32 IntVector3::getMax() const noexcept
	{
		return max(max(x, y), z);
	}
	
	Int32 IntVector3::getMin() const noexcept
	{
		return min(min(x, y), z);
	}
	
	Float IntVector3::getLength() const noexcept
	{
		return sqrtf(static_cast<Float>(getLengthSquared()));
	}
	
	Int32 IntVector3::getLengthSquared() const noexcept
	{
		return x * x + y * y + z * z;
	}
	
	IntVector3 operator+(const IntVector3& lhs, const IntVector3& rhs) noexcept
	{
		return { lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z };
	}
	
	IntVector3 operator-(const IntVector3& lhs, const IntVector3& rhs) noexcept
	{
		return { lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z };
	}
	IntVector3 operator*(const IntVector3& vector, const Int32 scale) noexcept
	{
		return { vector.x * scale, vector.y * scale, vector.z * scale };
	}
	IntVector3 operator*(const Int32 scale, const IntVector3& vector) noexcept
	{
		return { scale * vector.x, scale * vector.y, scale * vector.z };
	}
}
