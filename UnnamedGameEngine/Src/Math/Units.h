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
}