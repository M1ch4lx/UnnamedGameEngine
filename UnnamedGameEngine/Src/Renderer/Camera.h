#pragma once

#include "Math/Math.h"

namespace UEngine
{
	struct DenormalizedViewport
	{
		int Top;
		int Bottom;
		int Left;
		int Right;

		DenormalizedViewport() :
			Top(0), Bottom(1), Left(0), Right(1)
		{}

		DenormalizedViewport(int top, int left, int bottom, int right) :
			Top(top), Left(left), Bottom(bottom), Right(right)
		{}

		void Set(int top, int left, int bottom, int right)
		{
			Top = top;
			Left = left;
			Bottom = bottom;
			Right = right;
		}

		bool operator==(const DenormalizedViewport& other) const
		{
			return Left == other.Left && Right == other.Right
				&& Top == other.Top && Bottom == other.Bottom;
		}

		bool operator!=(const DenormalizedViewport& other) const
		{
			return !(*this == other);
		}
	};

	struct Viewport
	{
		float Top;
		float Bottom;
		float Left;
		float Right;

		Viewport() :
			Top(0.f), Bottom(1.f), Left(0.f), Right(1.f)
		{}

		Viewport(float top, float left, float bottom, float right) :
			Top(top), Left(left), Bottom(bottom), Right(right)
		{}

		void Set(float top, float left, float bottom, float right)
		{
			Top = top;
			Left = left;
			Bottom = bottom;
			Right = right;
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