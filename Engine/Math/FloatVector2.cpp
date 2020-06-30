#include "Engine/Math/FloatVector2.hpp"
#include "Engine/Math/utilities.hpp"

#include <cassert>

namespace nova
{
	constexpr Int32 k_min_index = 0;
	constexpr Int32 k_max_index = 2;


	const FloatVector2 FloatVector2::k_zero{ 0.0f, 0.0f };
	const FloatVector2 FloatVector2::k_unit_x{ 1.0f, 0.0f };
	const FloatVector2 FloatVector2::k_unit_y{ 0.0f, 1.0f };
	

	FloatVector2::FloatVector2(const Float uniform_value)
		: x{ uniform_value }, y{ uniform_value }{}

	FloatVector2::FloatVector2(const Float x_value, const Float y_value)
		: x{ x_value }, y{ y_value }{}

	FloatVector2::FloatVector2(const IntVector2& vector)
		: x{ static_cast<Float>(vector.x) }, y{ static_cast<Float>(vector.y) }{}

	const Float& FloatVector2::operator()(const Int32 index) const noexcept
	{
		assert(index >= k_min_index && index <= k_max_index);

		return (&x)[index];
	}

	Float& FloatVector2::operator()(const Int32 index) noexcept
	{
		assert(index >= k_min_index && index <= k_max_index);

		return (&x)[index];
	}

	const Float& FloatVector2::operator[](const Int32 index) const noexcept
	{
		assert(index >= k_min_index && index <= k_max_index);

		return (&x)[index];
	}

	Float& FloatVector2::operator[](const Int32 index) noexcept
	{
		assert(index >= k_min_index && index <= k_max_index);

		return (&x)[index];
	}

	Bool FloatVector2::operator==(const FloatVector2& other) const noexcept
	{
		return (x == other.x) && (y == other.y);
	}

	Bool FloatVector2::operator!=(const FloatVector2& other) const noexcept
	{
		return !((*this) == other);
	}

	FloatVector2& FloatVector2::operator+=(const FloatVector2& other) noexcept
	{
		x += other.x;
		y += other.y;

		return *this;
	}

	FloatVector2& FloatVector2::operator-=(const FloatVector2& other) noexcept
	{
		x -= other.x;
		y -= other.y;

		return *this;
	}

	FloatVector2& FloatVector2::operator*=(const FloatVector2& other) noexcept
	{
		x *= other.x;
		y *= other.y;

		return *this;
	}

	FloatVector2& FloatVector2::operator*=(const Float value) noexcept
	{
		x *= value;
		y *= value;

		return *this;
	}

	FloatVector2& FloatVector2::operator/=(const Float value) noexcept
	{
		assert(value != 0.0f);

		x /= value;
		y /= value;

		return *this;
	}

	FloatVector2 FloatVector2::operator+() const noexcept
	{
		return *this;
	}

	FloatVector2 FloatVector2::operator-() const noexcept
	{
		return { -x, -y };
	}

	Float FloatVector2::dot(const FloatVector2& other) const noexcept
	{
		return x * other.x + y * other.y;
	}

	Float FloatVector2::cross(const FloatVector2& other) const noexcept
	{
		return x * other.y - y * other.x;
	}

	Float FloatVector2::getMax() const noexcept
	{
		return max(x, y);
	}

	Float FloatVector2::getMin() const noexcept
	{
		return min(x, y);
	}

	Float FloatVector2::getLength() const noexcept
	{
		return sqrtf(getLengthSquared());
	}

	Float FloatVector2::getLengthSquared() const noexcept
	{
		return x * x + y * y;
	}

	void FloatVector2::normalize() noexcept
	{
		const auto length = getLength();

		assert(length != 0.0f);

		(*this) /= length;
	}

	Bool FloatVector2::isNormalized(const Float tolerance) const noexcept
	{
		const auto length = getLength();

		return abs(length - 1.0f) <= tolerance;
	}

	FloatVector2 operator+(const FloatVector2& lhs, const FloatVector2& rhs) noexcept
	{
		return {
			lhs.x + rhs.x,
			lhs.y + rhs.y
		};
	}

	FloatVector2 operator-(const FloatVector2& lhs, const FloatVector2& rhs) noexcept
	{
		return {
			lhs.x - rhs.x,
			lhs.y - rhs.y
		};
	}

	FloatVector2 operator*(const FloatVector2& lhs, const FloatVector2& rhs) noexcept
	{
		return {
			lhs.x * rhs.x,
			lhs.y * rhs.y
		};
	}

	FloatVector2 operator/(const FloatVector2& lhs, const FloatVector2& rhs) noexcept
	{
		assert(
			rhs.x != 0.0f &&
			rhs.y != 0.0f
		);

		return {
			lhs.x / rhs.x,
			lhs.y / rhs.y
		};
	}

	FloatVector2 operator+(const FloatVector2& vector, const Float value) noexcept
	{
		return {
			vector.x + value,
			vector.y + value
		};
	}

	FloatVector2 operator-(const FloatVector2& vector, const Float value) noexcept
	{
		return {
			vector.x - value,
			vector.y - value
		};
	}

	FloatVector2 operator*(const FloatVector2& vector, const Float value) noexcept
	{
		return {
			vector.x * value,
			vector.y * value
		};
	}

	FloatVector2 operator*(const Float value, const FloatVector2& vector) noexcept
	{
		return {
			value * vector.x,
			value * vector.y
		};
	}

	FloatVector2 operator/(const FloatVector2& vector, const Float value) noexcept
	{
		assert(value != 0.0f);

		return {
			vector.x / value,
			vector.y / value
		};
	}

	Float dot(const FloatVector2& lhs, const FloatVector2& rhs) noexcept
	{
		return lhs.dot(rhs);
	}

	Float cross(const FloatVector2& lhs, const FloatVector2& rhs) noexcept
	{
		return lhs.cross(rhs);
	}
}
