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
		// TODO: handle rotation around other axes
		return Math::Model(Position, Scale, Radians(Rotation.z));
	}
}