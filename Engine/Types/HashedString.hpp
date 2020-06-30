#pragma once

#include <string_view>

#include "Engine/Common/common.hpp"
#include "Engine/Types/fnv1a_hash.hpp"

namespace nova
{
	template <typename ValueType = char, typename HashType = UInt64>
	class NOVA_API HashedString
	{
	public:
		using hasher_type = fnv1a_Hasher<ValueType, HashType>;

		constexpr HashedString();

		template<Size_t N>
		explicit constexpr HashedString(const ValueType(&string)[N]) noexcept;

		explicit operator std::string_view() const noexcept;

		[[nodiscard]] HashType getHash() const noexcept;
		[[nodiscard]] std::string_view getString() const noexcept;
	private:
		const ValueType* value{ nullptr };
		HashType hash{};
	};

	template <typename ValueType, typename HashType>
	constexpr HashedString<ValueType, HashType>::HashedString()
		: hash{ hasher_type::hash(nullptr) }{}
	
	template <typename ValueType, typename HashType>
	HashedString<ValueType, HashType>::operator std::basic_string_view<char>() const noexcept
	{
		return value;
	}

	template <typename ValueType, typename HashType>
	HashType HashedString<ValueType, HashType>::getHash() const noexcept
	{
		return hash;
	}

	template <typename ValueType, typename HashType>
	std::string_view HashedString<ValueType, HashType>::getString() const noexcept
	{
		return value;
	}

	template <typename ValueType, typename HashType>
	template <std::size_t N>
	constexpr HashedString<ValueType, HashType>::HashedString(const ValueType(& string)[N]) noexcept
		: value {&string[0]}, hash{hasher_type::hash(&string[0])} {}
}
