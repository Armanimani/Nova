#include "Engine/Math/FloatVector4.hpp"
#include "Engine/Math/utilities.hpp"

#include <cassert>

namespace nova
{
	constexpr Int32 k_min_index = 0;
	constexpr Int32 k_max_index = 4;


	const FloatVector4 FloatVector4::k_zero{ 0.0f, 0.0f, 0.0f, 0.0f };
	const FloatVector4 FloatVector4::k_unit_x{ 1.0f, 0.0f, 0.0f, 0.0f };
	const FloatVector4 FloatVector4::k_unit_y{ 0.0f, 1.0f, 0.0f, 0.0f };
	const FloatVector4 FloatVector4::k_unit_z{ 0.0f, 0.0f, 1.0f, 0.0f };
	const FloatVector4 FloatVector4::k_unit_w{ 0.0f, 0.0f, 0.0f, 1.0f };


	FloatVector4::FloatVector4(const Float uniform_value)
		: x{ uniform_value }, y{ uniform_value }, z{ uniform_value }, w{ uniform_value }{}

	FloatVector4::FloatVector4(const Float x_value, const Float y_value, const Float z_value, const Float w_value)
		: x{ x_value }, y{ y_value }, z{ z_value }, w{ w_value }{}

	FloatVector4::FloatVector4(const IntVector2& vector)
		: x{ static_cast<Float>(vector.x) }, y{ static_cast<Float>(vector.y) }{}

	FloatVector4::FloatVector4(const IntVector3& vector)
		: x{ static_cast<Float>(vector.x) }, y{ static_cast<Float>(vector.y) }, z{ static_cast<Float>(vector.z) }{}

	FloatVector4::FloatVector4(const IntVector4& vector)
		: x{ static_cast<Float>(vector.x) }, y{ static_cast<Float>(vector.y) }, z{ static_cast<Float>(vector.z) }, w{ static_cast<Float>(vector.w) }{}
	
	FloatVector4::FloatVector4(const FloatVector2& vector)
		: x{ vector.x }, y{ vector.y }{}
	
	FloatVector4::FloatVector4(const FloatVector3& vector)
		: x{ vector.x }, y{ vector.y }, z{ vector.z }{}

	const Float& FloatVector4::operator()(const Int32 index) const noexcept
	{
		assert(index >= k_min_index && index <= k_max_index);

		return (&x)[index];
	}

	Float& FloatVector4::operator()(const Int32 index) noexcept
	{
		assert(index >= k_min_index && index <= k_max_index);

		return (&x)[index];
	}

	const Float& FloatVector4::operator[](const Int32 index) const noexcept
	{
		assert(index >= k_min_index && index <= k_max_index);

		return (&x)[index];
	}

	Float& FloatVector4::operator[](const Int32 index) noexcept
	{
		assert(index >= k_min_index && index <= k_max_index);

		return (&x)[index];
	}

	Bool FloatVector4::operator==(const FloatVector4& other) const noexcept
	{
		return (x == other.x) && (y == other.y) && (z == other.z) && (w == other.w);
	}

	Bool FloatVector4::operator!=(const FloatVector4& other) const noexcept
	{
		return !((*this) == other);
	}

	FloatVector4& FloatVector4::operator+=(const FloatVector4& other) noexcept
	{
		x += other.x;
		y += other.y;
		z += other.z;
		w += other.w;

		return *this;
	}

	FloatVector4& FloatVector4::operator-=(const FloatVector4& other) noexcept
	{
		x -= other.x;
		y -= other.y;
		z -= other.z;
		w -= other.w;

		return *this;
	}

	FloatVector4& FloatVector4::operator*=(const FloatVector4& other) noexcept
	{
		x *= other.x;
		y *= other.y;
		z *= other.z;
		w *= other.w;

		return *this;
	}

	FloatVector4& FloatVector4::operator*=(const Float value) noexcept
	{
		x *= value;
		y *= value;
		z *= value;
		w *= value;

		return *this;
	}

	FloatVector4& FloatVector4::operator/=(const Float value) noexcept
	{
		assert(value != 0.0f);

		x /= value;
		y /= value;
		z /= value;
		w /= value;

		return *this;
	}

	FloatVector4 FloatVector4::operator+() const noexcept
	{
		return *this;
	}

	FloatVector4 FloatVector4::operator-() const noexcept
	{
		return { -x, -y, -z, -w };
	}

	Float FloatVector4::dot(const FloatVector4& other) const noexcept
	{
		return x * other.x + y * other.y + z * other.z + w * other.w;
	}

	Float FloatVector4::getMax() const noexcept
	{
		return max(max(max(x, y), z), w);
	}

	Float FloatVector4::getMin() const noexcept
	{
		return min(min(min(x, y), z), w);
	}

	Float FloatVector4::getLength() const noexcept
	{
		return sqrtf(getLengthSquared());
	}

	Float FloatVector4::getLengthSquared() const noexcept
	{
		return x * x + y * y + z * z + w * w;
	}

	void FloatVector4::normalize() noexcept
	{
		const auto length = getLength();

		assert(length != 0.0f);

		(*this) /= length;
	}

	Bool FloatVector4::isNormalized(const Float tolerance) const noexcept
	{
		const auto length = getLength();

		return abs(length - 1.0f) <= tolerance;
	}

	FloatVector4 operator+(const FloatVector4& lhs, const FloatVector4& rhs) noexcept
	{
		return {
			lhs.x + rhs.x,
			lhs.y + rhs.y,
			lhs.z + rhs.z,
			lhs.w + rhs.w
		};
	}

	FloatVector4 operator-(const FloatVector4& lhs, const FloatVector4& rhs) noexcept
	{
		return {
			lhs.x - rhs.x,
			lhs.y - rhs.y,
			lhs.z - rhs.z,
			lhs.w - rhs.w
		};
	}

	FloatVector4 operator*(const FloatVector4& lhs, const FloatVector4& rhs) noexcept
	{
		return {
			lhs.x * rhs.x,
			lhs.y * rhs.y,
			lhs.z * rhs.z,
			lhs.w * rhs.w
		};
	}

	FloatVector4 operator/(const FloatVector4& lhs, const FloatVector4& rhs) noexcept
	{
		assert(
			rhs.x != 0.0f &&
			rhs.y != 0.0f &&
			rhs.z != 0.0f &&
			rhs.w != 0.0f
		);

		return {
			lhs.x / rhs.x,
			lhs.y / rhs.y,
			lhs.z / rhs.z,
			lhs.w / rhs.w
		};
	}

	FloatVector4 operator+(const FloatVector4& vector, const Float value) noexcept
	{
		return {
			vector.x + value,
			vector.y + value,
			vector.z + value,
			vector.w + value
		};
	}

	FloatVector4 operator-(const FloatVector4& vector, const Float value) noexcept
	{
		return {
			vector.x - value,
			vector.y - value,
			vector.z - value,
			vector.w - value
		};
	}

	FloatVector4 operator*(const FloatVector4& vector, const Float value) noexcept
	{
		return {
			vector.x * value,
			vector.y * value,
			vector.z * value,
			vector.w * value
		};
	}

	FloatVector4 operator*(const Float value, const FloatVector4& vector) noexcept
	{
		return {
			value * vector.x,
			value * vector.y,
			value * vector.z,
			value * vector.w
		};
	}

	FloatVector4 operator/(const FloatVector4& vector, const Float value) noexcept
	{
		assert(value != 0.0f);

		return {
			vector.x / value,
			vector.y / value,
			vector.z / value,
			vector.w / value
		};
	}

	Float dot(const FloatVector4& lhs, const FloatVector4& rhs) noexcept
	{
		return lhs.dot(rhs);
	}
}
