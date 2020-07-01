#include "Engine/Systems/Graphics/Context/GraphicContextFactory.hpp"
#include "Engine/DesignPatterns/ServiceLocator.hpp"
#include "Engine/Systems/Graphics/Platform/DirectX12/DX12GraphicContextFactoryAdapter.hpp"
#include "Engine/Logging/ConsoleLogger.hpp"

namespace nova
{
	std::unique_ptr<IGraphicContext> GraphicContextFactory::create(const GraphicSettings& settings, void* window_handle) noexcept
	{
		return getAdapter(settings.api)->createContext(settings, window_handle);
	}

	IGraphicContextFactoryAdapter* GraphicContextFactory::getAdapter(const GraphicApi api)
	{
		if (api == GraphicApi::direct_x12)
			ServiceLocator<IGraphicContextFactoryAdapter>::provide(std::make_unique<DX12GraphicContextFactoryAdapter>());
		else
			ConsoleLogger::logCritical(k_graphics_channel, "No api was specified for the graphic system!");

		return ServiceLocator<IGraphicContextFactoryAdapter>::get();
	}
}
