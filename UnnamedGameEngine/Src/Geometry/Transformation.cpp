#include "Pch.h"
#include "Transformation.h"

namespace UEngine
{
	void Transformable::SetTransformation(const Transformation& transformation)
	{
		this->transformation = transformation;
	}

	const Transformation& Transformable::GetTransformation() const
	{
		return transformation;
	}

	Matrix4 Transformation::ToMatrix() const
	{
		return ModelMatrix(
			Vector(position, 0.f),
			Vector(scale, 1.f),
			DegreesToRadians(rotation));
	}
}