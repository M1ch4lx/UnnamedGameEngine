#pragma once

#include "Math/Math.h"

namespace UEngine
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

	class Camera
	{
	public:
		virtual const Viewport& GetViewport() const = 0;

		virtual void SetViewport(const Viewport& viewport) = 0;

		virtual void SetRatio(const Vector2& ratio) = 0;

		virtual const Vector2& GetRatio() const = 0;

		virtual void SetSize(float size) = 0;

		virtual float GetSize() const = 0;

		virtual Vector2 GetDimensions() const = 0;

		virtual Matrix4 GetViewMatrix() const = 0;

		virtual Matrix4 GetProjectionMatrix() const = 0;
	};
}