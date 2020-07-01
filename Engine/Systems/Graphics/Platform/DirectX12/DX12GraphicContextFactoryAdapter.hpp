#pragma once

#include "Engine/Common/common.hpp"
#include "Engine/Systems/Graphics/Context/IGraphicContextFactoryAdapter.hpp"

namespace nova
{
	class NOVA_API DX12GraphicContextFactoryAdapter final : public IGraphicContextFactoryAdapter
	{
	public:
		[[nodiscard]] std::unique_ptr<IGraphicContext> createContext(
			const GraphicSettings& settings, void* window_handle) noexcept override;
	};
}
