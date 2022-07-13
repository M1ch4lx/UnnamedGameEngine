#pragma once

#include "Math/Math.h"

namespace UEngine
{
	struct Transformation
	{
		Vector3 Position;

		Vector3 Scale;

		Vector3 Rotation;

		Transformation() :
			Scale(1.f, 1.f, 1.f)
		{}

		// For now ignores 3D components
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