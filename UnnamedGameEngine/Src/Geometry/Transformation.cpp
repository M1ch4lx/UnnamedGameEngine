#include "Pch.h"
#include "Transformation.h"

namespace UEngine
{
	Transformable::Transformable()
	{

	}

	Transformation& Transformable::GetTransformation()
	{
		return transformation;
	}

	void Transformable::SetTransformation(const Transformation& transformation)
	{
		this->transformation = transformation;
	}
}