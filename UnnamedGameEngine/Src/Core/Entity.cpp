#include "Pch.h"
#include "Entity.h"

namespace UEngine
{
	Service<ComponentsManager> Entity::componentsService;

	void Entity::AttachComponent(Component* component)
	{
		component->owner = this;
		component->OnAttach();
	}

	void Entity::DetachComponent(Component* component)
	{
		component->OnDetach();
		component->owner = nullptr;
	}

	void Entity::InheritStatusFromParent()
	{
		if (parent && status.active)
		{
			parent->InheritStatusFromParent();
			status = parent->status;
		}
	}

	Entity::Entity() :
		parent(nullptr)
	{
		status.active = true;
	}

	Entity::~Entity()
	{
		RemoveAllComponents();
	}

	Component* Entity::GetComponent(ComponentTypeID typeId)
	{
		for (auto component : components)
		{
			if (component->typeId == typeId)
			{
				return component;
			}
		}
		return nullptr;
	}

	void Entity::RemoveAllComponents()
	{
		for (auto component : components)
		{
			DetachComponent(component);
		}
		components.clear();
	}

	void Entity::RemoveChild(Entity* child)
	{
		if (child->parent == this)
		{
			child->parent = nullptr;
		}
	}

	void Entity::AddChild(Entity* entity)
	{
		if (entity != this)
		{
			entity->parent = this;
		}
	}

	void Entity::Destroy()
	{
		status.active = false;
	}

	bool Entity::IsDestroyed() const
	{
		return !status.active;
	}

	Entity* Entity::Parent() const
	{
		return parent;
	}

	void EntitiesManager::OnDestroy()
	{
		entities.Clear();
	}

	Entity* EntitiesManager::CreateEntity()
	{
		return entities.Create();
	}

	void EntitiesManager::UpdateEntities()
	{
		for (auto entity : entities.Collection())
		{
			entity->InheritStatusFromParent();
		}

		entities.DeleteIf([](Entity* entity)
			{
				return entity->IsDestroyed();
			});
	}

	size_t EntitiesManager::CountEntities()
	{
		return entities.Size();
	}
}