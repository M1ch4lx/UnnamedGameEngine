#include "Pch.h"
#include "Service.h"

namespace UEngine
{
	Services& Services::Instance()
	{
		static Services serviceContainer;
		return serviceContainer;
	}

	Services::~Services()
	{
		DestroyServices();
	}

	void Services::DestroyServices()
	{
		auto& services = Instance().services;
		for (auto& serviceIndex : services)
		{
			if (serviceIndex.service)
			{
				serviceIndex.service->OnDestroy();
				delete serviceIndex.service;
			}
		}
		services.clear();
	}
}