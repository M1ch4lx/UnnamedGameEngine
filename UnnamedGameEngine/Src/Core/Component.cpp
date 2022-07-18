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

	ComponentTypeID ComponentsManager::GenerateComponentTypeID()
	{
		static ComponentTypeID id = 0;

		return id++;
	}

	void ComponentsManager::OnDestroy()
	{
		for (auto container : componentsContainers)
		{
			delete container;
		}
		componentsContainers.clear();
	}

	void ComponentsManager::UpdateComponents()
	{
		for (auto container : componentsContainers)
		{
			container->CleanupUnusedComponents();
		}
	}
}