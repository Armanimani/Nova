#pragma once

#include "Engine/Common/common.hpp"
#include "Engine/Types/base_types.hpp"
#include "Engine/Types/TypeIdentifier.hpp"
#include "Engine/Application/Context.hpp"

#include <array>

namespace nova
{
	class NOVA_API ISystem
	{
	public:
		ISystem() = default;
		ISystem(const ISystem& other) = default;
		ISystem(ISystem&& other) noexcept = default;
		ISystem& operator=(const ISystem& other) = default;
		ISystem& operator=(ISystem&& other) noexcept = default;
		
		virtual ~ISystem() = default;

		virtual void configure(Context* context) = 0;
		virtual void initialize(Context* context) noexcept = 0;
		virtual void update(Context* context, Float delta_time) noexcept = 0;
		virtual void finalize(Context* context) noexcept = 0;
	};

	template<typename...Component>
	struct NOVA_API ComponentPack
	{
		static std::array<UInt32, sizeof...(Component)> identification()
		{
			std::array<UInt32, sizeof...(Component)> result{};
			const std::initializer_list<UInt32> list = { TypeIdentifier::get<Component>()... };

			auto counter = 0;
			for (auto i = list.begin(); i != list.end(); ++i)
			{
				result[counter] = *i;
				counter++;
			}

			return result;
		}
	};

	template<typename MutableComponents, typename ImmutableComponents>
	class NOVA_API DescriptiveSystem: ISystem
	{
	public:
		using mutable_components = MutableComponents;
		using immutable_components = ImmutableComponents;
	};
}