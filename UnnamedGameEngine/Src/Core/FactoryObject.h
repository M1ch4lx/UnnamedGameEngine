#pragma once

namespace UEngine
{
	class FactoryObject
	{
	public:
		FactoryObject() = default;

		virtual ~FactoryObject() = default;

		FactoryObject(const FactoryObject&) = delete;

		FactoryObject(FactoryObject&&) = delete;

		FactoryObject& operator=(const FactoryObject&) = delete;

		FactoryObject& operator=(FactoryObject&&) = delete;
	};
}