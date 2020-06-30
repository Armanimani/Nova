#pragma once

#include "Engine/Common/common.hpp"
#include "Engine/Math/IntVector2.hpp"

namespace nova
{
	class NOVA_API FloatVector2
	{
	public:
		Float x{};
		Float y{};

		FloatVector2() = default;
		explicit FloatVector2(Float uniform_value);
		FloatVector2(Float x_value, Float y_value);

		explicit FloatVector2(const IntVector2& vector);

		FloatVector2(const FloatVector2&) = default;
		FloatVector2(FloatVector2&&) = default;

		FloatVector2& operator=(const FloatVector2&) noexcept = default;
		FloatVector2& operator=(FloatVector2&&) noexcept = default;

		~FloatVector2() = default;

		const Float& operator()(Int32 index) const noexcept;
		Float& operator()(Int32 index) noexcept;

		const Float& operator[](Int32 index) const noexcept;
		Float& operator[](Int32 index) noexcept;

		Bool operator==(const FloatVector2& other) const noexcept;
		Bool operator!=(const FloatVector2& other) const noexcept;

		FloatVector2& operator+=(const FloatVector2& other) noexcept;
		FloatVector2& operator-=(const FloatVector2& other) noexcept;
		FloatVector2& operator*=(const FloatVector2& other) noexcept;
		FloatVector2& operator*=(Float value) noexcept;
		FloatVector2& operator/=(Float value) noexcept;

		FloatVector2 operator+() const noexcept;
		FloatVector2 operator-() const noexcept;


		[[nodiscard]] Float dot(const FloatVector2& other) const noexcept;
		[[nodiscard]] Float cross(const FloatVector2& other) const noexcept;

		[[nodiscard]] Float getMax() const noexcept;
		[[nodiscard]] Float getMin() const noexcept;

		[[nodiscard]] Float getLength() const noexcept;
		[[nodiscard]] Float getLengthSquared() const noexcept;

		void normalize() noexcept;
		[[nodiscard]] Bool isNormalized(Float tolerance = 1.0E-5f) const noexcept;

		static const FloatVector2 k_zero;
		static const FloatVector2 k_unit_x;
		static const FloatVector2 k_unit_y;
	};


	/* Alignment checks */
	static_assert(offsetof(FloatVector2, y) == offsetof(FloatVector2, x) + 4, "FloatVector2 does not have the required alignment");


	/* operators */
	FloatVector2 operator+(const FloatVector2& lhs, const FloatVector2& rhs) noexcept;
	FloatVector2 operator-(const FloatVector2& lhs, const FloatVector2& rhs) noexcept;
	FloatVector2 operator*(const FloatVector2& lhs, const FloatVector2& rhs) noexcept;
	FloatVector2 operator/(const FloatVector2& lhs, const FloatVector2& rhs) noexcept;

	FloatVector2 operator+(const FloatVector2& vector, Float value) noexcept;
	FloatVector2 operator-(const FloatVector2& vector, Float value) noexcept;
	FloatVector2 operator*(const FloatVector2& vector, Float value) noexcept;
	FloatVector2 operator*(Float value, const FloatVector2& vector) noexcept;
	FloatVector2 operator/(const FloatVector2& vector, Float value) noexcept;


	/* Helper functions */
	[[nodiscard]] Float dot(const FloatVector2& lhs, const FloatVector2& rhs) noexcept;
	[[nodiscard]] Float cross(const FloatVector2& lhs, const FloatVector2& rhs) noexcept;
}
