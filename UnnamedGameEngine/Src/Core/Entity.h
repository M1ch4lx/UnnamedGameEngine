#pragma once

#include "Common.h"

#include "Service.h"
#include "Component.h"

namespace UEngine
{
	class Entity
	{
		friend class EntitiesManager;
	public:
		struct Status
		{
			bool active;
		};

	private:
		static Service<ComponentsManager> componentsService;

		Entity* parent;

		Status status;

		std::vector<Component*> components;

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
				try
				{
					component->owner = this;
					component->OnAttach();
					components.emplace_back(component);
				}
				catch (const AbortComponentException& exc)
				{
					component->owner = nullptr;
					// TODO: log error exc.Message()
				}
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
						component->OnDetach();
						component->owner = nullptr;
						return true;
					}
					return false;
				});
		}

		template<typename T>
		bool HasComponent()
		{
			return GetComponent<T>();
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

	private:
		void InheritStatusFromParent();
	};

	class EntitiesManager :public IService
	{
		SERVICE(EntitiesManager)
	private:
		Container<Entity> entities;

		virtual void OnDestroy() override;

	public:
		Entity* CreateEntity();

		void UpdateEntities();

		size_t CountEntities();
	};
}