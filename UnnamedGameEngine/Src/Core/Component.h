#pragma once

#include "Common.h"

#include "Service.h"
#include "System.h"
#include "Container.h"

namespace UEngine
{
	using ComponentTypeID = size_t;

	class Entity;

	class Component
	{
		friend class ComponentsService;
		friend class Entity;
	protected:
		Component();

		virtual ~Component() {};

		virtual void OnAttach() {};

		virtual void OnDetach() {};

	private:
		Entity* owner;

		ComponentTypeID typeId;

	public:
		Entity* Owner() const;

		ComponentTypeID Type() const;
	};

	class IComponentsContainer
	{
	public:
		virtual void CleanupUnusedComponents() = 0;

		virtual Component* CreateComponent() = 0;

		virtual void Clear() = 0;
	};

	template<class T>
	class ComponentsContainer :public IComponentsContainer
	{
		static_assert(std::is_base_of_v<Component, T>);
	private:
		Container<T> container;

	public:
		void CleanupUnusedComponents() override
		{
			container.DeleteIf([](T* component)
				{
					return !component->Owner();
				});
		}

		Component* CreateComponent() override
		{
			return reinterpret_cast<Component*>(container.Create());
		}

		void Clear() override
		{
			container.Clear();
		}

		std::vector<T*>& Collection()
		{
			return container.Collection();
		}
	};

	class ComponentsService :public IService
	{
		SERVICE(ComponentsService)
	private:
		ComponentTypeID GenerateComponentTypeID();

		std::vector<IComponentsContainer*> componentsContainers;

		void OnDestroy() override;

		template<typename T>
		ComponentTypeID InitializeComponentsContainer()
		{
			auto typeId = GenerateComponentTypeID();
			componentsContainers.resize(componentsContainers.size() + 1);
			componentsContainers[typeId] = reinterpret_cast<IComponentsContainer*>(new ComponentsContainer<T>());
			return typeId;
		}

		IComponentsContainer* GetComponentsContainer(ComponentTypeID typeId)
		{
			return componentsContainers[typeId];
		}

	public:
		template<typename T>
		ComponentTypeID GetComponentTypeID()
		{
			static_assert(std::is_base_of_v<Component, T>);

			static ComponentTypeID id = InitializeComponentsContainer<T>();
			return id;
		}

		template<typename T>
		std::vector<T*>& GetComponentsOfType()
		{
			return reinterpret_cast<ComponentsContainer<T>*>(GetComponentsContainer(GetComponentTypeID<T>()))->Collection();
		}

		template<typename T>
		T* CreateComponent()
		{
			auto typeId = GetComponentTypeID<T>();

			auto component = GetComponentsContainer(typeId)->CreateComponent();
			component->typeId = typeId;

			return reinterpret_cast<T*>(component);
		}

		void UpdateComponents();
	};

	class ComponentSystem :public ISystem
	{
	protected:
		Service<ComponentsService> componentsService;

	public:
		template<typename T>
		std::vector<T*>& Components()
		{
			return componentsService->GetComponentsOfType<T>();
		}
	};
}