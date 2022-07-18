#include "Pch.h"
#include "System.h"

namespace UEngine
{
	ISystem::ISystem() :
		running(false)
	{}

	void SystemsManager::OnDestroy()
	{
		for (auto system : systems)
		{
			delete system;
		}
		systems.clear();
		systems.shrink_to_fit();
	}

	inline void SystemsManager::RunSystem(ISystem* system)
	{
		if (!system->running)
		{
			system->Run();
			system->running = true;
		}
	}

	inline void SystemsManager::CloseSystem(ISystem* system)
	{
		if (system->running)
		{
			system->Close();
			system->running = false;
		}
	}

	inline void SystemsManager::UpdateSystem(ISystem* system)
	{
		if (system->running)
		{
			system->Update();
		}
	}

	void SystemsManager::RunSystems()
	{
		for (auto system : systems)
		{
			RunSystem(system);
		}
	}

	void SystemsManager::CloseSystems()
	{
		for (auto system : systems)
		{
			CloseSystem(system);
		}
	}

	void SystemsManager::UpdateSystems()
	{
		for (auto system : systems)
		{
			UpdateSystem(system);
		}
	}
}