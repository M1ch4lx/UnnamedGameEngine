#include "Pch.h"
#include "Vector.h"

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
		return Vector2(x * scalar, y * scalar);
	}

	Vector2 Vector2::Normalized() const
	{
		auto magnitude = Magnitude();
		return Vector2(x / magnitude, y / magnitude);
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

	float* Vector2::Data()
	{
		return reinterpret_cast<float*>(this);
	}

	Vector3::Vector3() :
		x(0.f), y(0.f), z(0.f)
	{}

	Vector3::Vector3(float x, float y, float z) :
		x(x), y(y), z(z)
	{

	}

	void Vector3::Set(float x, float y, float z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}

	Vector3 Vector3::operator+(const Vector3& vec) const
	{
		return Vector3(x + vec.x, y + vec.y, z + vec.z);
	}

	Vector3 Vector3::operator-(const Vector3& vec) const
	{
		return Vector3(x - vec.x, y - vec.y, z - vec.z);
	}

	Vector3 Vector3::operator*(float scalar) const
	{
		return Vector3(x * scalar, y * scalar, z * scalar);
	}

	Vector3 Vector3::Normalized() const
	{
		auto magnitude = Magnitude();
		return Vector3(x / magnitude, y / magnitude, z / magnitude);
	}

	void Vector3::operator+=(const Vector3& vec)
	{
		x += vec.x;
		y += vec.y;
		z += vec.z;
	}

	void Vector3::operator-=(const Vector3& vec)
	{
		x -= vec.x;
		y -= vec.y;
		z -= vec.z;
	}

	void Vector3::operator*=(float scalar)
	{
		x *= scalar;
		y *= scalar;
		z *= scalar;
	}

	void Vector3::Normalize()
	{
		auto magnitude = Magnitude();
		x /= magnitude;
		y /= magnitude;
		z /= magnitude;
	}

	inline float Vector3::Magnitude() const
	{
		return std::sqrt((x * x) + (y * y) + (z * z));
	}

	inline float Vector3::SquaredMagnitude() const
	{
		return (x * x) + (y * y) + (z * z);
	}

	float* Vector3::Data()
	{
		return reinterpret_cast<float*>(this);
	}

	Vector4::Vector4() :
		x(0.f), y(0.f), z(0.f), w(0.f)
	{}

	Vector4::Vector4(float x, float y, float z, float w) :
		x(x), y(y), z(z), w(w)
	{}

	void Vector4::Set(float x, float y, float z, float w)
	{
		this->x = x;
		this->y = y;
		this->z = z;
		this->w = w;
	}

	float* Vector4::Data()
	{
		return reinterpret_cast<float*>(this);
	}

	Vector2& Vector2View(float* data)
	{
		return *reinterpret_cast<Vector2*>(data);
	}

	Vector3& Vector3View(float* data)
	{
		return *reinterpret_cast<Vector3*>(data);
	}

	Vector4& Vector4View(float* data)
	{
		return *reinterpret_cast<Vector4*>(data);
	}
}