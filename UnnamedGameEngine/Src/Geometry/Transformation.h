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

		Matrix4 ToMatrix() const;
	};

	class Transformable
	{
	protected:
		Transformation transformation;

	public:
		void SetTransformation(const Transformation& transformation);

		Transformation& GetTransformation();

		virtual ~Transformable() = default;
	};
}