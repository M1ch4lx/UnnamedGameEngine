#pragma once

namespace UEngine
{
	struct Rect
	{
		float Top;
		float Bottom;
		float Left;
		float Right;

		Rect() :
			Top(0.f), Bottom(0.f), Left(0.f), Right(0.f)
		{}

		Rect(const Vector2& size)
		{
			const float halfWidth = size.x / 2.f;
			const float halfHeight = size.y / 2.f;

			Top = halfHeight;
			Bottom = -halfHeight;
			Left = -halfWidth;
			Right = halfWidth;
		}
	};
}