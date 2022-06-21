#pragma once

#include "Math/Math.h"

namespace Atron
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
		static Transformation defaultTransformation;

		Transformation* transformation;

	public:
		Transformable();
		
		virtual ~Transformable() {};

		const Transformation* GetTransformation() const;

		void SetTransformation(Transformation* transformation);

		void ClearTransformation();
	};
}