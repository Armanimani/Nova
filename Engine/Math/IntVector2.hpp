#pragma once

#include "Engine/Common/common.hpp"

namespace nova
{
	class NOVA_API IntVector2
	{
	public:
		Int32 x{};
		Int32 y{};

		IntVector2() = default;
		explicit IntVector2(Int32 uniform_value);
		IntVector2(Int32 x_value, Int32 y_value);

		IntVector2(const IntVector2&) = default;
		IntVector2(IntVector2&&) = default;

		IntVector2& operator=(const IntVector2&) noexcept = default;
		IntVector2& operator=(IntVector2&&) noexcept = default;

		~IntVector2() = default;
		
		const Int32& operator()(Int32 index) const noexcept;
		Int32& operator()(Int32 index) noexcept;
		
		const Int32& operator[](Int32 index) const noexcept;
		Int32& operator[](Int32 index) noexcept;

		Bool operator==(const IntVector2& other) const noexcept;
		Bool operator!=(const IntVector2& other) const noexcept;

		IntVector2& operator+=(const IntVector2& other) noexcept;
		IntVector2& operator-=(const IntVector2& other) noexcept;
		IntVector2& operator*=(Int32 value) noexcept;

		[[nodiscard]] Int32 getMax() const noexcept;
		[[nodiscard]] Int32 getMin() const noexcept;
		
		[[nodiscard]] Float getLength() const noexcept;
		[[nodiscard]] Int32 getLengthSquared() const noexcept;

		static const IntVector2 k_zero;
		static const IntVector2 k_unit_x;
		static const IntVector2 k_unit_y;
	};


	/* Alignment checks */
	static_assert(offsetof(IntVector2, y) == offsetof(IntVector2, x) + 4, "IntVector2 does not have the required alignment");

	
	/* Operators */
	IntVector2 operator+(const IntVector2& lhs, const IntVector2& rhs) noexcept;
	IntVector2 operator-(const IntVector2& lhs, const IntVector2& rhs) noexcept;
	IntVector2 operator*(const IntVector2& vector, Int32 scale) noexcept;
	IntVector2 operator*(Int32 scale, const IntVector2& vector) noexcept;
}
