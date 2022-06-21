#pragma once

#include "Common.h"
#include "Container.h"
#include "Service.h"

namespace Atron
{
	template<typename Target>
	class FactoryTarget
	{
	public:
		virtual Target* Create() const = 0;

		virtual size_t TargetSize() const = 0;
	};

	template<typename Target, typename TargetImpl>
	class FactoryTargetImpl :public FactoryTarget<Target>
	{
		static_assert(std::is_base_of_v<Target, TargetImpl>);
	public:
		Target* Create() const override
		{
			return reinterpret_cast<Target*>(new TargetImpl());
		}

		size_t TargetSize() const override
		{
			return sizeof(TargetImpl);
		}
	};

	template<typename Target>
	class Fabricator :public IService
	{
		SERVICE(Fabricator<Target>)
	private:
		FactoryTarget<Target>* factoryTarget;

		void CheckFactoryTarget()
		{
			if (!factoryTarget)
			{
				throw std::exception("No factory target");
			}
		}

		void OnCreate() override
		{
			factoryTarget = nullptr;
		}

		void OnDestroy() override
		{
			delete factoryTarget;
		}

	public:
		template<typename TargetImpl>
		void SetImplementation()
		{
			delete factoryTarget;
			factoryTarget = new FactoryTargetImpl<Target, TargetImpl>();
		}
		
		Target* Create()
		{
			CheckFactoryTarget();
			return factoryTarget->Create();
		}

		void Destroy(Target* target)
		{
			delete target;
		}
	};

	template<typename Target, typename TargetImpl>
	void SetFactoryImplementation()
	{
		Service<Fabricator<Target>>()->SetImplementation<TargetImpl>();
	}

	template<typename Target>
	class Fabricate
	{
	private:
		static Service<Fabricator<Target>> fabricator;

		Target* target;

	public:
		Fabricate() :
			target(fabricator->Create())
		{}

		~Fabricate()
		{
			fabricator->Destroy(target);
		}

		Target* operator->()
		{
			return target;
		}

		Target* Obtain()
		{
			auto ptr = target;
			target = nullptr;
			return ptr;
		}
	};

	template<typename Target>
	Service<Fabricator<Target>> Fabricate<Target>::fabricator;
}