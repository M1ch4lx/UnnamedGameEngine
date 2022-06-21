#pragma once

#include <cmath>

namespace Atron
{
	class Vector2
	{
	public:
		float x;
		float y;

		Vector2();

		Vector2(float x, float y);

		void Set(float x, float y);

		Vector2 operator+(const Vector2& vec) const;

		Vector2 operator-(const Vector2& vec) const;

		Vector2 operator*(float scalar) const;

		Vector2 Normalized() const;

		void operator+=(const Vector2& vec);

		void operator-=(const Vector2& vec);

		void operator*=(float scalar);

		void Normalize();

		float Magnitude() const;

		float SquaredMagnitude() const;
	};
}