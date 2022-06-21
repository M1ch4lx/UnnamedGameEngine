#pragma once

#include "Core/Component.h"

#include <iostream>

namespace UEngine
{
	struct Vec
	{
		float x = 0.f;
		float y = 0.f;
	};

	class Transform :public Component
	{
	private:
		Vec position;

		virtual void OnAttach() override
		{
			std::cout << "Transform attached" << std::endl;
		}

		virtual void OnDetach() override
		{
			std::cout << "Transfom detached" << std::endl;
		}

	public:
		Vec& GetPosition()
		{
			return position;
		}
	};
}