#pragma once

#include <memory>

#include "Engine/Common/common.hpp"
#include "Engine/Systems/Graphics/Settings/GraphicSettings.hpp"
#include "Engine/Systems/Graphics/Context/IGraphicContext.hpp"

namespace nova
{
	class NOVA_API IGraphicContextFactoryAdapter
	{
	public:
		virtual ~IGraphicContextFactoryAdapter() = default;
		
		[[nodiscard]] virtual std::unique_ptr<IGraphicContext> createContext(
			const GraphicSettings& settings, void* window_handle) noexcept = 0;
	};
}