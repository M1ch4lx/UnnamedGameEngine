#pragma once

#include <cmath>

namespace UEngine
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

		float* Data();
	};

	class Vector3
	{
	public:
		union
		{
			Vector2 xy;
			struct
			{
				float x;
				float y;
			};
		};
		float z;

		Vector3();

		Vector3(float x, float y, float z);

		void Set(float x, float y, float z);

		Vector3 operator+(const Vector3& vec) const;

		Vector3 operator-(const Vector3& vec) const;

		Vector3 operator*(float scalar) const;

		Vector3 Normalized() const;

		void operator+=(const Vector3& vec);

		void operator-=(const Vector3& vec);

		void operator*=(float scalar);

		void Normalize();

		float Magnitude() const;

		float SquaredMagnitude() const;

		float* Data();
	};

	class Vector4
	{
	public:
		union
		{
			Vector3 xyz;
			struct
			{
				float x;
				float y;
				float z;
			};
		};
		float w;

		Vector4();

		Vector4(float x, float y, float z, float w=1.f);

		void Set(float x, float y, float z, float w=1.f);

		float* Data();
	};

	class Color3
	{
	public:
		float r;
		float g;
		float b;

		Color3() :
			r(0.f), g(0.f), b(0.f)
		{}

		Color3(float r, float g, float b) :
			r(r), g(g), b(b)
		{}
	};

	class Color4
	{
	public:
		union
		{
			Color3 rgb;
			struct
			{
				float r;
				float g;
				float b;
			};
		};
		float a;

		Color4() :
			r(0.f), g(0.f), b(0.f), a(1.f)
		{}

		Color4(float r, float g, float b, float a) :
			r(r), g(g), b(b), a(a)
		{}

		Color4(const Color3& rgb, float a) :
			rgb(rgb), a(a)
		{}
	};

	Color3 Color(float r, float g, float b);

	Color4 Color(float r, float g, float b, float a);

	Color4 Color(const Color3& color3, float a);

	Vector2& Vector2View(float* data);

	Vector3& Vector3View(float* data);

	Vector4& Vector4View(float* data);

	Vector2 Vector(float x, float y);

	Vector3 Vector(float x, float y, float z);

	Vector3 Vector(const Vector2& vec2, float z);

	Vector4 Vector(float x, float y, float z, float w);

	Vector4 Vector(const Vector3& vec3, float w);

	Vector4 Vector(const Vector2& vec2, float z, float w);
}