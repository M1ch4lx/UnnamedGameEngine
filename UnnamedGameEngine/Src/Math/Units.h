#pragma once

#include <cmath>

namespace UEngine
{
	constexpr float Pi()
	{
		return 3.14159265358979323846f;
	}

	constexpr float Radians(float degrees)
	{
		return (degrees / 180.f) * Pi();
	}

	constexpr float PixelCordinates(float pixelsPerUnit, float units)
	{
		return units * pixelsPerUnit;
	}

	constexpr float UnitCordinates(float pixelsPerUnit, float pixels)
	{
		return pixels / pixelsPerUnit;
	}

	inline Vector2 PixelCordinates(float pixelsPerUnit, const Vector2& units)
	{
		return units * pixelsPerUnit;
	}

	inline Vector2 UnitCordinates(float pixelsPerUnit, const Vector2& pixels)
	{
		return pixels / pixelsPerUnit;
	}
}