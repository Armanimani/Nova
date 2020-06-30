#pragma once

#include "Engine/Common/common.hpp"
#include "Engine/Math/IntVector2.hpp"
#include "Engine/Math/IntVector3.hpp"

namespace nova
{
	class NOVA_API FloatVector3
	{
	public:
		Float x{};
		Float y{};
		Float z{};

		FloatVector3() = default;
		explicit FloatVector3(Float uniform_value);
		FloatVector3(Float x_value, Float y_value, Float z_value);

		explicit FloatVector3(const IntVector2& vector);
		explicit FloatVector3(const IntVector3& vector);

		FloatVector3(const FloatVector3&) = default;
		FloatVector3(FloatVector3&&) = default;
		
		FloatVector3& operator=(const FloatVector3&) noexcept = default;
		FloatVector3& operator=(FloatVector3&&) noexcept = default;

		~FloatVector3() = default;

		const Float& operator()(Int32 index) const noexcept;
		Float& operator()(Int32 index) noexcept;

		const Float& operator[](Int32 index) const noexcept;
		Float& operator[](Int32 index) noexcept;

		Bool operator==(const FloatVector3& other) const noexcept;
		Bool operator!=(const FloatVector3& other) const noexcept;

		FloatVector3& operator+=(const FloatVector3& other) noexcept;
		FloatVector3& operator-=(const FloatVector3& other) noexcept;
		FloatVector3& operator*=(const FloatVector3& other) noexcept;
		FloatVector3& operator*=(Float value) noexcept;
		FloatVector3& operator/=(Float value) noexcept;
		
		FloatVector3 operator+() const noexcept;
		FloatVector3 operator-() const noexcept;
		

		[[nodiscard]] Float dot(const FloatVector3& other) const noexcept;
		[[nodiscard]] FloatVector3 cross(const FloatVector3& other) const noexcept;
		
		[[nodiscard]] Float getMax() const noexcept;
		[[nodiscard]] Float getMin() const noexcept;

		[[nodiscard]] Float getLength() const noexcept;
		[[nodiscard]] Float getLengthSquared() const noexcept;

		void normalize() noexcept;
		[[nodiscard]] Bool isNormalized(Float tolerance = 1.0E-5f) const noexcept;

		static const FloatVector3 k_zero;
		static const FloatVector3 k_unit_x;
		static const FloatVector3 k_unit_y;
		static const FloatVector3 k_unit_z;
		static const FloatVector3 k_up;
		static const FloatVector3 k_down;
		static const FloatVector3 k_right;
		static const FloatVector3 k_left;
		static const FloatVector3 k_forward;
		static const FloatVector3 k_backward;
	};


	/* Alignment checks */
	static_assert(offsetof(FloatVector3, y) == offsetof(FloatVector3, x) + 4, "FloatVector3 does not have the required alignment");
	static_assert(offsetof(FloatVector3, z) == offsetof(FloatVector3, x) + 8, "FloatVector3 does not have the required alignment");

	
	/* operators */
	FloatVector3 operator+(const FloatVector3& lhs, const FloatVector3& rhs) noexcept;
	FloatVector3 operator-(const FloatVector3& lhs, const FloatVector3& rhs) noexcept;
	FloatVector3 operator*(const FloatVector3& lhs, const FloatVector3& rhs) noexcept;
	FloatVector3 operator/(const FloatVector3& lhs, const FloatVector3& rhs) noexcept;

	FloatVector3 operator+(const FloatVector3& vector, Float value) noexcept;
	FloatVector3 operator-(const FloatVector3& vector, Float value) noexcept;
	FloatVector3 operator*(const FloatVector3& vector, Float value) noexcept;
	FloatVector3 operator*(Float value, const FloatVector3& vector) noexcept;
	FloatVector3 operator/(const FloatVector3& vector, Float value) noexcept;

	
	/* Helper functions */
	[[nodiscard]] Float dot(const FloatVector3& lhs, const FloatVector3& rhs) noexcept;
	[[nodiscard]] FloatVector3 cross(const FloatVector3& lhs, const FloatVector3& rhs) noexcept;
}
