#include "Pch.h"
#include "System.h"

namespace UEngine
{
	ISystem::ISystem() :
		running(false)
	{}

	void SystemsService::OnDestroy()
	{
		for (auto system : systems)
		{
			delete system;
		}
		systems.clear();
		systems.shrink_to_fit();
	}

	inline void SystemsService::RunSystem(ISystem* system)
	{
		if (!system->running)
		{
			system->Run();
			system->running = true;
		}
	}

	inline void SystemsService::CloseSystem(ISystem* system)
	{
		if (system->running)
		{
			system->Close();
			system->running = false;
		}
	}

	inline void SystemsService::UpdateSystem(ISystem* system)
	{
		if (system->running)
		{
			system->Update();
		}
	}

	void SystemsService::RunSystems()
	{
		for (auto system : systems)
		{
			RunSystem(system);
		}
	}

	void SystemsService::CloseSystems()
	{
		for (auto system : systems)
		{
			CloseSystem(system);
		}
	}

	void SystemsService::UpdateSystems()
	{
		for (auto system : systems)
		{
			UpdateSystem(system);
		}
	}
}