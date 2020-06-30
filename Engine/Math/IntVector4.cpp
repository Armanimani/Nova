#include "Engine/Math/IntVector4.hpp"
#include "Engine/Math/utilities.hpp"

#include <cassert>

namespace nova
{
	constexpr Int32 k_min_index = 0;
	constexpr Int32 k_max_index = 3;

	
	const IntVector4 IntVector4::k_zero{ 0, 0, 0, 0 };
	const IntVector4 IntVector4::k_unit_x{ 1, 0, 0, 0 };
	const IntVector4 IntVector4::k_unit_y{ 0, 1, 0, 0 };
	const IntVector4 IntVector4::k_unit_z{ 0, 0, 1, 0 };
	const IntVector4 IntVector4::k_unit_w{ 0, 0, 0, 1 };

	
	IntVector4::IntVector4(const Int32 uniform_value)
		: x{ uniform_value }, y{ uniform_value }, z{ uniform_value }, w{ uniform_value }{}

	IntVector4::IntVector4(const Int32 x_value, const Int32 y_value, const Int32 z_value, const Int32 w_value)
		: x{ x_value }, y{ y_value }, z{ z_value }, w{ w_value }{}

	IntVector4::IntVector4(const IntVector2& vector)
		: x{ vector.x }, y{ vector.y } {}
	
	IntVector4::IntVector4(const IntVector3& vector)
		: x{ vector.x }, y{ vector.y }, z{ vector.z } {}

	const Int32& IntVector4::operator()(const Int32 index) const noexcept
	{
		assert(index >= k_min_index && index <= k_max_index);

		return (&x)[index];
	}

	Int32& IntVector4::operator()(const Int32 index) noexcept
	{
		assert(index >= k_min_index && index <= k_max_index);

		return (&x)[index];
	}

	const Int32& IntVector4::operator[](const Int32 index) const noexcept
	{
		assert(index >= k_min_index && index <= k_max_index);

		return (&x)[index];
	}

	Int32& IntVector4::operator[](const Int32 index) noexcept
	{
		assert(index >= k_min_index && index <= k_max_index);

		return (&x)[index];
	}

	Bool IntVector4::operator==(const IntVector4& other) const noexcept
	{
		return (x == other.x) && (y == other.y) && (z == other.z) && (w == other.w);
	}

	Bool IntVector4::operator!=(const IntVector4& other) const noexcept
	{
		return !((*this) == other);
	}

	IntVector4& IntVector4::operator+=(const IntVector4& other) noexcept
	{
		x += other.x;
		y += other.y;
		z += other.z;
		w += other.w;

		return *this;
	}

	IntVector4& IntVector4::operator-=(const IntVector4& other) noexcept
	{
		x -= other.x;
		y -= other.y;
		z -= other.z;
		w -= other.w;

		return *this;
	}

	IntVector4& IntVector4::operator*=(const Int32 value) noexcept
	{
		x *= value;
		y *= value;
		z *= value;
		w *= value;

		return *this;
	}

	Int32 IntVector4::getMax() const noexcept
	{
		return max(max(max(x, y), z), w);
	}

	Int32 IntVector4::getMin() const noexcept
	{
		return min(min(min(x, y), z), w);
	}

	Float IntVector4::getLength() const noexcept
	{
		return sqrtf(static_cast<Float>(getLengthSquared()));
	}

	Int32 IntVector4::getLengthSquared() const noexcept
	{
		return x * x + y * y + z * z + w * w;
	}

	IntVector4 operator+(const IntVector4& lhs, const IntVector4& rhs) noexcept
	{
		return { lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z, lhs.w + rhs.w };
	}

	IntVector4 operator-(const IntVector4& lhs, const IntVector4& rhs) noexcept
	{
		return { lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z, lhs.w - rhs.w };
	}
	IntVector4 operator*(const IntVector4& vector, const Int32 scale) noexcept
	{
		return { vector.x * scale, vector.y * scale, vector.z * scale, vector.w * scale };
	}
	IntVector4 operator*(const Int32 scale, const IntVector4& vector) noexcept
	{
		return { scale * vector.x, scale * vector.y, scale * vector.z, scale * vector.w };
	}
}
