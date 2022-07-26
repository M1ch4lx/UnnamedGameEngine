#pragma once

#include "Transform.h"

namespace UEngine
{
	class TransformSystem :public ComponentSystem
	{
		SYSTEM(TransformSystem)
	public:
		virtual void Update() override;

		virtual void Run() override;

		virtual void Close() override;
	};
}