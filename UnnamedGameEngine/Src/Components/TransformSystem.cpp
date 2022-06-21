#include "Pch.h"
#include "TransformSystem.h"

namespace UEngine
{
	void TransformSystem::Update()
	{
		for (auto component : Components<Transform>())
		{
			std::cout << component->GetPosition().x << std::endl;
		}
	}

	void TransformSystem::Run()
	{
		std::cout << "Run" << std::endl;
	}

	void TransformSystem::Close()
	{
		std::cout << "Close" << std::endl;
	}
}