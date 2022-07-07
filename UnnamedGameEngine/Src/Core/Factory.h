#pragma once

#include "Common.h"
#include "Container.h"
#include "Service.h"

namespace UEngine
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
		
		Ref<Target> Create()
		{
			CheckFactoryTarget();
			return Ref<Target>(factoryTarget->Create());
		}
	};

	template<typename Target, typename TargetImpl>
	void SetFactoryImplementation()
	{
		Service<Fabricator<Target>>()->SetImplementation<TargetImpl>();
	}

	template<typename Target>
	Ref<Target> Create()
	{
		static Service<Fabricator<Target>> fabricator;

		return fabricator->Create();
	}
}