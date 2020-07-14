#pragma once

#include "Engine/Systems/Graphics/Context/IGraphicContext.hpp"
#include "Engine/Systems/Graphics/Renderer/IRenderer.hpp"
#include "Engine/Systems//ISystem.hpp"
#include "Engine/Common/common.hpp"

#include <memory>


namespace nova
{
	class NOVA_API GraphicSystem final: public ISystem
	{
	public:
		void configure(Context* context) noexcept override;
		void initialize(Context* context) noexcept override;
		void update(Context* context, Float delta_time) noexcept override;
		void finalize(Context* context) noexcept override;
	private:
		std::unique_ptr<IGraphicContext> graphic_context{ nullptr };
		std::vector<std::unique_ptr<IRenderer>> renderer_list{};

		static void initializeComponent(Context* context) noexcept;

		void registerRenderer() noexcept;
		void initializeRendererList(IGraphicCommandContext* command_context) noexcept;
		void updateRendererList(Context* context, Float delta_time) noexcept;
		void finalizeRendererList() noexcept;

		void processResizeEvent(const EventManager& event_manager) noexcept;
	};
}
