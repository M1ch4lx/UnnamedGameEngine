#pragma once

#include "Math/Math.h"

namespace UEngine
{
	struct Transformation2D
	{
		Vector2 Position;

		float Depth;

		Vector2 Scale;

		float Rotation;

		Transformation2D() :
			Scale(1.f, 1.f), Rotation(0.f), Depth(0.f)
		{}

		Matrix4 ToMatrix() const;
	};

	class Transformable2D
	{
	protected:
		Transformation2D transformation;

	public:
		void SetTransformation(const Transformation2D& transformation);

		Transformation2D& GetTransformation();

		virtual ~Transformable2D() = default;
	};
}