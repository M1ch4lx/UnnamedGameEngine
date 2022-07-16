#include "Pch.h"
#include "Transformation2D.h"

namespace UEngine
{
	void Transformable2D::SetTransformation(const Transformation2D& transformation)
	{
		this->transformation = transformation;
	}

	Transformation2D& Transformable2D::GetTransformation()
	{
		return transformation;
	}

	Matrix4 Transformation2D::ToMatrix() const
	{
		return Math::Model(Vector(Position, Depth), Vector(Scale, 1.f), Radians(Rotation));
	}
}