#pragma once

#include "Common.h"

#include "Service.h"
#include "Component.h"

namespace Atron
{
	class Entity
	{
		friend class EntitiesService;
	public:
		struct Status
		{
			bool active;
		};

	private:
		static Service<ComponentsService> componentsService;

		Entity* parent;

		Status status;

		std::vector<Component*> components;

		void AttachComponent(Component* component);

		void DetachComponent(Component* component);

		void InheritStatusFromParent();

	public:
		Entity();

		~Entity();

		Component* GetComponent(ComponentTypeID typeId);

		template<typename T>
		void AddComponent()
		{
			if (!GetComponent(componentsService->GetComponentTypeID<T>()))
			{
				auto component = componentsService->CreateComponent<T>();
				AttachComponent(component);
				components.emplace_back(component);
			}
		}

		template<typename T>
		T* GetComponent()
		{
			return reinterpret_cast<T*>(GetComponent(componentsService->GetComponentTypeID<T>()));
		}

		template<typename T>
		void RemoveComponent()
		{
			auto type = componentsService->GetComponentTypeID<T>();
			std::erase_if(components, [type, this](Component* component)
				{
					if (component->Type() == type)
					{
						DetachComponent(component);
						return true;
					}
					return false;
				});
		}

		void RemoveAllComponents();

		void RemoveChild(Entity* child);

		void AddChild(Entity* entity);

		void Destroy();

		bool IsDestroyed() const;

		Entity* Parent() const;

		Entity(const Entity&) = delete;
		Entity(Entity&&) = delete;
		Entity& operator=(const Entity&) = delete;
		Entity& operator=(Entity&&) = delete;
	};

	class EntitiesService :public IService
	{
		SERVICE(EntitiesService)
	private:
		Container<Entity> entities;

		virtual void OnDestroy() override;

	public:
		Entity* CreateEntity();

		void UpdateEntities();

		size_t CountEntities();
	};
}