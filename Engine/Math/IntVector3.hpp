#pragma once

#include "Engine/Common/common.hpp"
#include "Engine/Math/IntVector2.hpp"

namespace nova
{
	class NOVA_API IntVector3
	{
	public:
		Int32 x{};
		Int32 y{};
		Int32 z{};

		IntVector3() = default;
		explicit IntVector3(Int32 uniform_value);
		IntVector3(Int32 x_value, Int32 y_value, Int32 z_value);

		explicit IntVector3(const IntVector2& vector);

		IntVector3(const IntVector3&) = default;
		IntVector3(IntVector3&&) = default;

		IntVector3& operator=(const IntVector3&) noexcept = default;
		IntVector3& operator=(IntVector3&&) noexcept = default;

		~IntVector3() = default;

		const Int32& operator()(Int32 index) const noexcept;
		Int32& operator()(Int32 index) noexcept;

		const Int32& operator[](Int32 index) const noexcept;
		Int32& operator[](Int32 index) noexcept;

		Bool operator==(const IntVector3& other) const noexcept;
		Bool operator!=(const IntVector3& other) const noexcept;

		IntVector3& operator+=(const IntVector3& other) noexcept;
		IntVector3& operator-=(const IntVector3& other) noexcept;
		IntVector3& operator*=(Int32 value) noexcept;

		[[nodiscard]] Int32 getMax() const noexcept;
		[[nodiscard]] Int32 getMin() const noexcept;

		[[nodiscard]] Float getLength() const noexcept;
		[[nodiscard]] Int32 getLengthSquared() const noexcept;

		static const IntVector3 k_zero;
		static const IntVector3 k_unit_x;
		static const IntVector3 k_unit_y;
		static const IntVector3 k_unit_z;
		static const IntVector3 k_up;
		static const IntVector3 k_down;
		static const IntVector3 k_right;
		static const IntVector3 k_left;
		static const IntVector3 k_forward;
		static const IntVector3 k_backward;
	};


	/* Alignment checks */
	static_assert(offsetof(IntVector3, y) == offsetof(IntVector3, x) + 4, "IntVector3 does not have the required alignment");
	static_assert(offsetof(IntVector3, z) == offsetof(IntVector3, x) + 8, "IntVector3 does not have the required alignment");


	/* Operators */
	IntVector3 operator+(const IntVector3& lhs, const IntVector3& rhs) noexcept;
	IntVector3 operator-(const IntVector3& lhs, const IntVector3& rhs) noexcept;
	IntVector3 operator*(const IntVector3& vector, Int32 scale) noexcept;
	IntVector3 operator*(Int32 scale, const IntVector3& vector) noexcept;
}
