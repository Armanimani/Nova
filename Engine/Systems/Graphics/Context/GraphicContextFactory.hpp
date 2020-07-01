#pragma once

#include <memory>

#include "Engine/Common/common.hpp"
#include "Engine/Systems/Graphics/Settings/GraphicSettings.hpp"
#include "Engine/Systems/Graphics/Context/IGraphicContext.hpp"
#include "Engine/Systems/Graphics/Context/IGraphicContextFactoryAdapter.hpp"

namespace nova
{
	class NOVA_API GraphicContextFactory
	{
	public:
		static std::unique_ptr<IGraphicContext> create(const GraphicSettings& settings, void* window_handle) noexcept;
	private:
		static IGraphicContextFactoryAdapter* getAdapter(GraphicApi api);
	};
}
