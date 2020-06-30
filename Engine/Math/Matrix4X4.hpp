#pragma once

#include "Engine/Common/common.hpp"
#include "Engine/Math/FloatVector4.hpp"

namespace nova
{
	class NOVA_API Matrix4X4
	{
	public:
		Float data[4][4] {};

		Matrix4X4() = default;
		Matrix4X4(const FloatVector4& row_1, const FloatVector4& row_2, const FloatVector4& row_3, const FloatVector4& row_4);

		~Matrix4X4() = default;

		const Float& operator()(Int32 row_index, Int32 column_index) const noexcept;
		Float& operator()(Int32 row_index, Int32 column_index) noexcept;
	};

	
	/* Alignment checks */
	static_assert(offsetof(Matrix4X4, data[0][1]) == offsetof(Matrix4X4, data[0][0]) + 1 * sizeof(Float), "Matrix4X4 does not have the required alignment");
	static_assert(offsetof(Matrix4X4, data[0][2]) == offsetof(Matrix4X4, data[0][0]) + 2 * sizeof(Float), "Matrix4X4 does not have the required alignment");
	static_assert(offsetof(Matrix4X4, data[0][3]) == offsetof(Matrix4X4, data[0][0]) + 3 * sizeof(Float), "Matrix4X4 does not have the required alignment");
	static_assert(offsetof(Matrix4X4, data[1][0]) == offsetof(Matrix4X4, data[0][0]) + 4 * sizeof(Float), "Matrix4X4 does not have the required alignment");
	static_assert(offsetof(Matrix4X4, data[1][1]) == offsetof(Matrix4X4, data[0][0]) + 5 * sizeof(Float), "Matrix4X4 does not have the required alignment");
	static_assert(offsetof(Matrix4X4, data[1][2]) == offsetof(Matrix4X4, data[0][0]) + 6 * sizeof(Float), "Matrix4X4 does not have the required alignment");
	static_assert(offsetof(Matrix4X4, data[1][3]) == offsetof(Matrix4X4, data[0][0]) + 7 * sizeof(Float), "Matrix4X4 does not have the required alignment");
	static_assert(offsetof(Matrix4X4, data[2][0]) == offsetof(Matrix4X4, data[0][0]) + 8 * sizeof(Float), "Matrix4X4 does not have the required alignment");
	static_assert(offsetof(Matrix4X4, data[2][1]) == offsetof(Matrix4X4, data[0][0]) + 9 * sizeof(Float), "Matrix4X4 does not have the required alignment");
	static_assert(offsetof(Matrix4X4, data[2][2]) == offsetof(Matrix4X4, data[0][0]) + 10 * sizeof(Float), "Matrix4X4 does not have the required alignment");
	static_assert(offsetof(Matrix4X4, data[2][3]) == offsetof(Matrix4X4, data[0][0]) + 11 * sizeof(Float), "Matrix4X4 does not have the required alignment");
	static_assert(offsetof(Matrix4X4, data[3][0]) == offsetof(Matrix4X4, data[0][0]) + 12 * sizeof(Float), "Matrix4X4 does not have the required alignment");
	static_assert(offsetof(Matrix4X4, data[3][1]) == offsetof(Matrix4X4, data[0][0]) + 13 * sizeof(Float), "Matrix4X4 does not have the required alignment");
	static_assert(offsetof(Matrix4X4, data[3][2]) == offsetof(Matrix4X4, data[0][0]) + 14 * sizeof(Float), "Matrix4X4 does not have the required alignment");
	static_assert(offsetof(Matrix4X4, data[3][3]) == offsetof(Matrix4X4, data[0][0]) + 15 * sizeof(Float), "Matrix4X4 does not have the required alignment");
}
