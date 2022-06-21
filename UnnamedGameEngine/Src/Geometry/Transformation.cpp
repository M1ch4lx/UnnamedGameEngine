#include "Pch.h"
#include "Transformation.h"

namespace Atron
{
	Transformation Transformable::defaultTransformation;

	Transformable::Transformable() :
		transformation(&defaultTransformation)
	{

	}

	const Transformation* Transformable::GetTransformation() const
	{
		return transformation;
	}

	void Transformable::SetTransformation(Transformation* transformation)
	{
		this->transformation = transformation ? transformation : &defaultTransformation;
	}

	void Transformable::ClearTransformation()
	{
		SetTransformation(nullptr);
	}
}