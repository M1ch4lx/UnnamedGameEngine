#include "Pch.h"
#include "Component.h"

namespace UEngine
{
	Component::Component() :
		owner(nullptr), typeId(-1)
	{}

	Entity* Component::Owner() const
	{
		return owner;
	}

	ComponentTypeID Component::Type() const
	{
		return typeId;
	}

	ComponentTypeID ComponentsService::GenerateComponentTypeID()
	{
		static ComponentTypeID id = 0;

		return id++;
	}

	void ComponentsService::OnDestroy()
	{
		for (auto container : componentsContainers)
		{
			delete container;
		}
		componentsContainers.clear();
	}

	void ComponentsService::UpdateComponents()
	{
		for (auto container : componentsContainers)
		{
			container->CleanupUnusedComponents();
		}
	}
}