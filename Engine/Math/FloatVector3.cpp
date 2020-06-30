#include "Engine/Math/FloatVector3.hpp"
#include "Engine/Math/utilities.hpp"

#include <cassert>

namespace nova
{
	constexpr Int32 k_min_index = 0;
	constexpr Int32 k_max_index = 3;


	const FloatVector3 FloatVector3::k_zero{ 0.0f, 0.0f, 0.0f };
	const FloatVector3 FloatVector3::k_unit_x{ 1.0f, 0.0f, 0.0f };
	const FloatVector3 FloatVector3::k_unit_y{ 0.0f, 1.0f, 0.0f };
	const FloatVector3 FloatVector3::k_unit_z{ 0.0f, 0.0f, 1.0f };
	const FloatVector3 FloatVector3::k_up{ 0.0f, 0.0f, 1.0f };
	const FloatVector3 FloatVector3::k_down{ 0.0f, 0.0f, -1.0f };
	const FloatVector3 FloatVector3::k_right{ 0.0f, 1.0f, 0.0f };
	const FloatVector3 FloatVector3::k_left{ 0.0f, -1.0f, 0.0f };
	const FloatVector3 FloatVector3::k_forward{ 1.0f, 0.0f, 0.0f };
	const FloatVector3 FloatVector3::k_backward{ -1.0f, 0.0f, 0.0f };
	
	
	FloatVector3::FloatVector3(const Float uniform_value)
		: x{ uniform_value }, y{ uniform_value }, z{ uniform_value } {}

	FloatVector3::FloatVector3(const Float x_value, const Float y_value, const Float z_value)
		: x{ x_value }, y{ y_value }, z{ z_value }{}

	FloatVector3::FloatVector3(const IntVector2& vector)
		: x{ static_cast<Float>(vector.x) }, y{ static_cast<Float>(vector.y) }{}
	
	FloatVector3::FloatVector3(const IntVector3& vector)
		: x{ static_cast<Float>(vector.x) }, y{ static_cast<Float>(vector.y) }, z{ static_cast<Float>(vector.z) }{}

	const Float& FloatVector3::operator()(const Int32 index) const noexcept
	{
		assert(index >= k_min_index && index <= k_max_index);

		return (&x)[index];
	}
	
	Float& FloatVector3::operator()(const Int32 index) noexcept
	{
		assert(index >= k_min_index && index <= k_max_index);

		return (&x)[index];
	}
	
	const Float& FloatVector3::operator[](const Int32 index) const noexcept
	{
		assert(index >= k_min_index && index <= k_max_index);

		return (&x)[index];
	}
	
	Float& FloatVector3::operator[](const Int32 index) noexcept
	{
		assert(index >= k_min_index && index <= k_max_index);

		return (&x)[index];
	}
	
	Bool FloatVector3::operator==(const FloatVector3& other) const noexcept
	{
		return (x == other.x) && (y == other.y) && (z == other.z);
	}
	
	Bool FloatVector3::operator!=(const FloatVector3& other) const noexcept
	{
		return !((*this) == other);
	}
	
	FloatVector3& FloatVector3::operator+=(const FloatVector3& other) noexcept
	{
		x += other.x;
		y += other.y;
		z += other.z;
		
		return *this;
	}
	
	FloatVector3& FloatVector3::operator-=(const FloatVector3& other) noexcept
	{
		x -= other.x;
		y -= other.y;
		z -= other.z;

		return *this;
	}
	
	FloatVector3& FloatVector3::operator*=(const FloatVector3& other) noexcept
	{
		x *= other.x;
		y *= other.y;
		z *= other.z;

		return *this;
	}
	
	FloatVector3& FloatVector3::operator*=(const Float value) noexcept
	{
		x *= value;
		y *= value;
		z *= value;

		return *this;
	}
	
	FloatVector3& FloatVector3::operator/=(const Float value) noexcept
	{
		assert(value != 0.0f);

		x /= value;
		y /= value;
		z /= value;

		return *this;
	}
	
	FloatVector3 FloatVector3::operator+() const noexcept
	{
		return *this;
	}
	
	FloatVector3 FloatVector3::operator-() const noexcept
	{
		return { -x, -y, -z };
	}
	
	Float FloatVector3::dot(const FloatVector3& other) const noexcept
	{
		return x * other.x + y * other.y + z * other.z;
	}
	
	FloatVector3 FloatVector3::cross(const FloatVector3& other) const noexcept
	{
		const auto x_value = y * other.z - z * other.y;
		const auto y_value = z * other.x - x * other.z;
		const auto z_value = x * other.y - y * other.x;

		return { x_value, y_value, z_value };
	}
	
	Float FloatVector3::getMax() const noexcept
	{
		return max(max(x, y), z);
	}
	
	Float FloatVector3::getMin() const noexcept
	{
		return min(min(x, y), z);
	}
	
	Float FloatVector3::getLength() const noexcept
	{
		return sqrtf(getLengthSquared());
	}
	
	Float FloatVector3::getLengthSquared() const noexcept
	{
		return x * x + y * y + z * z;
	}
	
	void FloatVector3::normalize() noexcept
	{
		const auto length = getLength();

		assert(length != 0.0f);
		
		(*this) /= length;
	}
	
	Bool FloatVector3::isNormalized(const Float tolerance) const noexcept
	{
		const auto length = getLength();
		
		return abs(length - 1.0f) <= tolerance;
	}
	
	FloatVector3 operator+(const FloatVector3& lhs, const FloatVector3& rhs) noexcept
	{
		return {
			lhs.x + rhs.x,
			lhs.y + rhs.y,
			lhs.z + rhs.z
		};
	}
	
	FloatVector3 operator-(const FloatVector3& lhs, const FloatVector3& rhs) noexcept
	{
		return {
			lhs.x - rhs.x,
			lhs.y - rhs.y,
			lhs.z - rhs.z
		};
	}
	
	FloatVector3 operator*(const FloatVector3& lhs, const FloatVector3& rhs) noexcept
	{
		return {
			lhs.x * rhs.x,
			lhs.y * rhs.y,
			lhs.z * rhs.z
		};
	}
	
	FloatVector3 operator/(const FloatVector3& lhs, const FloatVector3& rhs) noexcept
	{
		assert(
			rhs.x != 0.0f && 
			rhs.y != 0.0f && 
			rhs.z != 0.0f
		);
		
		return {
			lhs.x / rhs.x,
			lhs.y / rhs.y,
			lhs.z / rhs.z
		};
	}
	
	FloatVector3 operator+(const FloatVector3& vector, const Float value) noexcept
	{
		return {
			vector.x + value,
			vector.y + value,
			vector.z + value
		};
	}
	
	FloatVector3 operator-(const FloatVector3& vector, const Float value) noexcept
	{
		return {
			vector.x - value,
			vector.y - value,
			vector.z - value
		};
	}
	
	FloatVector3 operator*(const FloatVector3& vector, const Float value) noexcept
	{
		return {
			vector.x * value,
			vector.y * value,
			vector.z * value
		};
	}
	
	FloatVector3 operator*(const Float value, const FloatVector3& vector) noexcept
	{
		return {
			value * vector.x,
			value * vector.y,
			value * vector.z
		};
	}
	
	FloatVector3 operator/(const FloatVector3& vector, const Float value) noexcept
	{
		assert(value != 0.0f);
		
		return {
			vector.x / value,
			vector.y / value,
			vector.z / value
		};
	}
	
	Float dot(const FloatVector3& lhs, const FloatVector3& rhs) noexcept
	{
		return lhs.dot(rhs);
	}
	
	FloatVector3 cross(const FloatVector3& lhs, const FloatVector3& rhs) noexcept
	{
		return lhs.cross(rhs);
	}
}
