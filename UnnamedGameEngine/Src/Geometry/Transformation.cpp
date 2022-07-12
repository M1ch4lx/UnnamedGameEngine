#include "Pch.h"
#include "Transformation.h"

namespace UEngine
{
	void Transformable::SetTransformation(const Transformation& transformation)
	{
		this->transformation = transformation;
	}

	Transformation& Transformable::GetTransformation()
	{
		return transformation;
	}

	Matrix4 Transformation::ToMatrix() const
	{
		return Math::Model(
			Vector(position, 0.f),
			Vector(scale, 1.f),
			Radians(rotation));
	}
}