#include "Pch.h"
#include "Vector2.h"

namespace UEngine
{
	Vector2::Vector2() :
		x(0.f), y(0.f)
	{}

	Vector2::Vector2(float x, float y) :
		x(x), y(y)
	{}

	void Vector2::Set(float x, float y)
	{
		this->x = x;
		this->y = y;
	}

	Vector2 Vector2::operator+(const Vector2& vec) const
	{
		return Vector2(x + vec.x, y + vec.y);
	}

	Vector2 Vector2::operator-(const Vector2& vec) const
	{
		return Vector2(x - vec.x, y - vec.y);
	}

	Vector2 Vector2::operator*(float scalar) const
	{
		auto magnitude = Magnitude();
		return Vector2(x / magnitude, y / magnitude);
	}

	Vector2 Vector2::Normalized() const
	{

		return Vector2();
	}

	void Vector2::operator+=(const Vector2& vec)
	{
		x += vec.x;
		y += vec.y;
	}

	void Vector2::operator-=(const Vector2& vec)
	{
		x -= vec.x;
		y -= vec.y;
	}

	void Vector2::operator*=(float scalar)
	{
		x *= scalar;
		y *= scalar;
	}

	void Vector2::Normalize()
	{
		auto magnitude = Magnitude();
		x /= magnitude;
		y /= magnitude;
	}

	inline float Vector2::Magnitude() const
	{
		return std::sqrt((x * x) + (y * y));
	}

	inline float Vector2::SquaredMagnitude() const
	{
		return (x * x) + (y * y);
	}
}