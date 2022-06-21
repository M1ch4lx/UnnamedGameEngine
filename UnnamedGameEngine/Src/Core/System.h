#pragma once

#include "Common.h"

#include "Service.h"

namespace UEngine
{
	class ISystem
	{
		friend class SystemsService;
	private:
		bool running;

	protected:
		virtual void Update() = 0;

		virtual void Run() = 0;

		virtual void Close() = 0;

		ISystem();

		virtual ~ISystem() {};
	};

	class SystemsService :public IService
	{
		SERVICE(SystemsService)
	private:
		std::vector<ISystem*> systems;

		template<typename TSystem>
		TSystem* InitializeSystem()
		{
			static_assert(std::is_base_of_v<ISystem, TSystem>);

			auto system = new TSystem();
			systems.reserve(systems.capacity() + 1);
			systems.emplace_back(system);
			return system;
		}

		virtual void OnDestroy() override;

		void RunSystem(ISystem* system);

		void CloseSystem(ISystem* system);

		void UpdateSystem(ISystem* system);

	public:
		template<typename TSystem>
		TSystem* Get()
		{
			static auto system = InitializeSystem<TSystem>();
			return system;
		}

		template<typename TSystem>
		void Restart()
		{
			auto system = Get<TSystem>();
			CloseSystem(system);
			RunSystem(system);
		}

		void RunSystems();

		void CloseSystems();

		void UpdateSystems();
	};

	template<typename TSystem>
	class System
	{
		static_assert(std::is_base_of_v<ISystem, TSystem>);
	private:
		static Service<SystemsService> systemsService;
	
		TSystem* system;

	public:
		System() :
			system(systemsService->Get<TSystem>())
		{}

		System(const System&) = delete;
		System(System&&) = delete;
		System& operator=(const System&) = delete;
		System& operator=(System&&) = delete;

		TSystem* operator->()
		{
			return system;
		}
	};

	template<typename TSystem>
	Service<SystemsService> System<TSystem>::systemsService;
}

#define SYSTEM(className) friend class SystemsService; private: virtual ~className() {}; className() {};