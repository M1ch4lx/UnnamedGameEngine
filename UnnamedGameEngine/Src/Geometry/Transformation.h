#pragma once

#include "Math/Math.h"

namespace UEngine
{
	struct Transformation
	{
		Vector2 position;

		Vector2 scale;

		float rotation;

		Transformation() :
			scale(1.f, 1.f), rotation(0.f)
		{}
	};

	class Transformable
	{
	private:
		Transformation transformation;

	public:
		Transformable();
		
		virtual ~Transformable() = default;

		Transformation& GetTransformation();

		void SetTransformation(const Transformation& transformation);
	};
}