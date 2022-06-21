#pragma once

#include "Core/Common.h"

#include "Math/Math.h"

#include "Geometry/Transformation.h"

namespace Atron
{
	struct Viewport
	{
		Vector2 begin;

		Vector2 end;

		Viewport() :
			begin(0.f, 0.f), end(1.f, 1.f)
		{}

		Viewport(float xBegin, float yBegin, float xEnd, float yEnd) :
			begin(xBegin, yBegin), end(xEnd, yEnd)
		{}

		void Set(float xBegin, float yBegin, float xEnd, float yEnd)
		{
			begin.Set(xBegin, yBegin);
			end.Set(xEnd, yEnd);
		}
	};

	class Camera :public Transformable
	{
	private:
		static constexpr float SIZE_MULTIPLIER = 10.f;

		Viewport viewport;

		Vector2 ratio;

		float size;

	public:
		Camera();

		const Viewport& GetViewport() const;

		void SetViewport(const Viewport& viewport);

		void SetRatio(const Vector2& ratio);

		const Vector2& GetRatio() const;

		void SetSize(float size);

		float GetSize() const;

		Vector2 CalculateSize() const;
	};
}