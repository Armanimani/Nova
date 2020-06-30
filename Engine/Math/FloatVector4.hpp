#pragma once

#include "Engine/Common/common.hpp"
#include "Engine/Math/IntVector2.hpp"
#include "Engine/Math/IntVector3.hpp"
#include "Engine/Math/IntVector4.hpp"
#include "Engine/Math/FloatVector2.hpp"
#include "Engine/Math/FloatVector3.hpp"

namespace nova
{
	class NOVA_API FloatVector4
	{
	public:
		Float x{};
		Float y{};
		Float z{};
		Float w{};

		FloatVector4() = default;
		explicit FloatVector4(Float uniform_value);
		FloatVector4(Float x_value, Float y_value, Float z_value, Float w_value);

		explicit FloatVector4(const IntVector2& vector);
		explicit FloatVector4(const IntVector3& vector);
		explicit FloatVector4(const IntVector4& vector);
		explicit FloatVector4(const FloatVector2& vector);
		explicit FloatVector4(const FloatVector3& vector);

		FloatVector4(const FloatVector4&) = default;
		FloatVector4(FloatVector4&&) = default;

		FloatVector4& operator=(const FloatVector4&) noexcept = default;
		FloatVector4& operator=(FloatVector4&&) noexcept = default;

		~FloatVector4() = default;

		const Float& operator()(Int32 index) const noexcept;
		Float& operator()(Int32 index) noexcept;

		const Float& operator[](Int32 index) const noexcept;
		Float& operator[](Int32 index) noexcept;

		Bool operator==(const FloatVector4& other) const noexcept;
		Bool operator!=(const FloatVector4& other) const noexcept;

		FloatVector4& operator+=(const FloatVector4& other) noexcept;
		FloatVector4& operator-=(const FloatVector4& other) noexcept;
		FloatVector4& operator*=(const FloatVector4& other) noexcept;
		FloatVector4& operator*=(Float value) noexcept;
		FloatVector4& operator/=(Float value) noexcept;

		FloatVector4 operator+() const noexcept;
		FloatVector4 operator-() const noexcept;


		[[nodiscard]] Float dot(const FloatVector4& other) const noexcept;

		[[nodiscard]] Float getMax() const noexcept;
		[[nodiscard]] Float getMin() const noexcept;

		[[nodiscard]] Float getLength() const noexcept;
		[[nodiscard]] Float getLengthSquared() const noexcept;

		void normalize() noexcept;
		[[nodiscard]] Bool isNormalized(Float tolerance = 1.0E-5f) const noexcept;

		static const FloatVector4 k_zero;
		static const FloatVector4 k_unit_x;
		static const FloatVector4 k_unit_y;
		static const FloatVector4 k_unit_z;
		static const FloatVector4 k_unit_w;
	};


	/* Alignment checks */
	static_assert(offsetof(FloatVector4, y) == offsetof(FloatVector4, x) + 4, "FloatVector4 does not have the required alignment");
	static_assert(offsetof(FloatVector4, z) == offsetof(FloatVector4, x) + 8, "FloatVector4 does not have the required alignment");
	static_assert(offsetof(FloatVector4, w) == offsetof(FloatVector4, x) + 12, "FloatVector4 does not have the required alignment");


	/* operators */
	FloatVector4 operator+(const FloatVector4& lhs, const FloatVector4& rhs) noexcept;
	FloatVector4 operator-(const FloatVector4& lhs, const FloatVector4& rhs) noexcept;
	FloatVector4 operator*(const FloatVector4& lhs, const FloatVector4& rhs) noexcept;
	FloatVector4 operator/(const FloatVector4& lhs, const FloatVector4& rhs) noexcept;

	FloatVector4 operator+(const FloatVector4& vector, Float value) noexcept;
	FloatVector4 operator-(const FloatVector4& vector, Float value) noexcept;
	FloatVector4 operator*(const FloatVector4& vector, Float value) noexcept;
	FloatVector4 operator*(Float value, const FloatVector4& vector) noexcept;
	FloatVector4 operator/(const FloatVector4& vector, Float value) noexcept;


	/* Helper functions */
	[[nodiscard]] Float dot(const FloatVector4& lhs, const FloatVector4& rhs) noexcept;
}
