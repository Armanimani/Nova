#pragma once

#include "Engine/Common/common.hpp"
#include "Engine/Types/base_types.hpp"
#include "Engine/Systems/ISystem.hpp"
#include "Engine/Application/Context.hpp"

#include <memory>
#include <vector>

namespace nova
{
	class NOVA_API Application
	{
	public:
		Application();
		~Application() = default;

		void addSystem(std::unique_ptr<ISystem>&& pipeline);

		template<typename Settings>
		void addSettings(Settings settings) noexcept;
		
		void start() noexcept;
	private:
		std::vector<std::unique_ptr<ISystem>> systems{};
		std::unique_ptr<Context> context{ nullptr };

		void configure() noexcept;
		void initialize() noexcept;
		void update() noexcept;
		void finalize() noexcept;

		void updateContext() const noexcept;

		void configureSystems() noexcept;
		void initializeSystems() noexcept;
		void updateSystems(Float delta_time) noexcept;
		void finalizeSystems() noexcept;
	};

	template <typename Settings>
	void Application::addSettings(Settings settings) noexcept
	{
		context->entity_manager.reserve<Settings>(1);
		context->entity_manager.emplace<Settings>(context->master_entity, settings);
	}
}
