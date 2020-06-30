#include "Engine/Math/Matrix4X4.hpp"

#include <cassert>

namespace nova
{
	constexpr Int32 k_min_index = 0;
	constexpr Int32 k_max_index = 3;

	
	Matrix4X4::Matrix4X4(const FloatVector4& row_1, const FloatVector4& row_2, const FloatVector4& row_3, const FloatVector4& row_4)
	{
		data[0][0] = row_1.x;
		data[0][1] = row_1.y;
		data[0][2] = row_1.z;
		data[0][3] = row_1.w;

		data[1][0] = row_2.x;
		data[1][1] = row_2.y;
		data[1][2] = row_2.z;
		data[1][3] = row_2.w;

		data[2][0] = row_3.x;
		data[2][1] = row_3.y;
		data[2][2] = row_3.z;
		data[2][3] = row_3.w;

		data[3][0] = row_4.x;
		data[3][1] = row_4.y;
		data[3][2] = row_4.z;
		data[3][3] = row_4.w;
	}

	const Float& Matrix4X4::operator()(const Int32 row_index, const Int32 column_index) const noexcept
	{
		assert(row_index >= k_min_index && row_index <= k_max_index);
		assert(column_index >= k_min_index && column_index <= k_max_index);
		
		return data[row_index][column_index];
	}
	
	Float& Matrix4X4::operator()(const Int32 row_index, const Int32 column_index) noexcept
	{
		assert(row_index >= k_min_index && row_index <= k_max_index);
		assert(column_index >= k_min_index && column_index <= k_max_index);

		return data[row_index][column_index];
	}
}
