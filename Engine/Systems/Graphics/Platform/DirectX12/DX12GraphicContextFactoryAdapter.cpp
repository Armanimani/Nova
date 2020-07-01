#include "Engine/Systems/Graphics/Platform/DirectX12/DX12GraphicContextFactoryAdapter.hpp"
#include "Engine/Systems/Graphics/Platform/DirectX12/DX12GraphicContext.hpp"

namespace nova
{
	std::unique_ptr<IGraphicContext> DX12GraphicContextFactoryAdapter::createContext(
		const GraphicSettings& settings, void* window_handle) noexcept
	{
		return std::make_unique<DX12GraphicContext>(settings, window_handle);
	}
}
