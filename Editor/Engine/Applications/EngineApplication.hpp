#pragma once

#include <Engine/Application/Application.hpp>
#include <thread>

#include "Editor/Engine/Applications/EngineSettings.hpp"

namespace nova::editor
{
	class EngineApplication
	{
	public:
		EngineApplication(EngineSettings settings);

		~EngineApplication();
		
		void start();	
	private:
		std::unique_ptr<Application> application{};
		std::unique_ptr<std::thread> thread{};
		EngineSettings settings{};
	};
}