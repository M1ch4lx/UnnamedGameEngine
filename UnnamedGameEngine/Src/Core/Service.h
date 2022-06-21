#pragma once

#include "Common.h"

#include "Core.h"

namespace Atron
{
	class IService
	{
		friend class Services;
	protected:
		virtual void OnCreate() {};

		virtual void OnDestroy() {};

		virtual ~IService() {};
	};

	class Services
	{
	private:
		struct ServiceIndex
		{
			IService* service;

			ServiceIndex() :
				service(nullptr)
			{}

			ServiceIndex(IService* service) :
				service(service)
			{}
		};

		static Services& Instance();

		std::list<ServiceIndex> services;

		ServiceIndex* CreateServiceIndex()
		{
			services.emplace_back();

			return &services.back();
		}

		template<typename TService>
		static ServiceIndex* GetServiceIndex()
		{
			static_assert(std::is_base_of_v<IService, TService>);

			static auto serviceIndex = Instance().CreateServiceIndex();

			return serviceIndex;
		}

		static void DestroyServices();

		Services() {};

		~Services();

	public:
		template<typename TService>
		static TService* Get()
		{
			auto serviceIndex = GetServiceIndex<TService>();

			if (serviceIndex->service == nullptr)
			{
				serviceIndex->service = reinterpret_cast<IService*>(new TService());

				serviceIndex->service->OnCreate();
			}

			return reinterpret_cast<TService*>(serviceIndex->service);
		}
	};

	template<typename TService>
	class Service
	{
		static_assert(std::is_base_of_v<IService, TService>);
	private:
		TService* service;

	public:
		Service() :
			service(Services::Get<TService>())
		{}

		Service(const Service&) = delete;
		Service(Service&&) = delete;
		Service& operator=(const Service&) = delete;
		Service& operator=(Service&&) = delete;

		TService* operator->()
		{
			return service;
		}
	};
}

#define SERVICE(className) friend class Services; private: virtual ~className() {}; className() {};