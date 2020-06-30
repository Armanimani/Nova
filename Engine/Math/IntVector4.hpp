#pragma once

#include "Engine/Common/common.hpp"
#include "Engine/Math/IntVector2.hpp"
#include "Engine/Math/IntVector3.hpp"

namespace nova
{
	class NOVA_API IntVector4
	{
	public:
		Int32 x{};
		Int32 y{};
		Int32 z{};
		Int32 w{};

		IntVector4() = default;
		explicit IntVector4(Int32 uniform_value);
		IntVector4(Int32 x_value, Int32 y_value, Int32 z_value, Int32 w_value);

		explicit IntVector4(const IntVector2& vector);
		explicit IntVector4(const IntVector3& vector);
		
		IntVector4(const IntVector4&) = default;
		IntVector4(IntVector4&&) = default;

		IntVector4& operator=(const IntVector4&) noexcept = default;
		IntVector4& operator=(IntVector4&&) noexcept = default;

		~IntVector4() = default;

		const Int32& operator()(Int32 index) const noexcept;
		Int32& operator()(Int32 index) noexcept;

		const Int32& operator[](Int32 index) const noexcept;
		Int32& operator[](Int32 index) noexcept;

		Bool operator==(const IntVector4& other) const noexcept;
		Bool operator!=(const IntVector4& other) const noexcept;

		IntVector4& operator+=(const IntVector4& other) noexcept;
		IntVector4& operator-=(const IntVector4& other) noexcept;
		IntVector4& operator*=(Int32 value) noexcept;

		[[nodiscard]] Int32 getMax() const noexcept;
		[[nodiscard]] Int32 getMin() const noexcept;

		[[nodiscard]] Float getLength() const noexcept;
		[[nodiscard]] Int32 getLengthSquared() const noexcept;

		static const IntVector4 k_zero;
		static const IntVector4 k_unit_x;
		static const IntVector4 k_unit_y;
		static const IntVector4 k_unit_z;
		static const IntVector4 k_unit_w;
	};


	/* Alignment checks */
	static_assert(offsetof(IntVector4, y) == offsetof(IntVector4, x) + 4, "IntVector4 does not have the required alignment");
	static_assert(offsetof(IntVector4, z) == offsetof(IntVector4, x) + 8, "IntVector4 does not have the required alignment");
	static_assert(offsetof(IntVector4, w) == offsetof(IntVector4, x) + 12, "IntVector4 does not have the required alignment");


	/* Operators */
	IntVector4 operator+(const IntVector4& lhs, const IntVector4& rhs) noexcept;
	IntVector4 operator-(const IntVector4& lhs, const IntVector4& rhs) noexcept;
	IntVector4 operator*(const IntVector4& vector, Int32 scale) noexcept;
	IntVector4 operator*(Int32 scale, const IntVector4& vector) noexcept;
}
