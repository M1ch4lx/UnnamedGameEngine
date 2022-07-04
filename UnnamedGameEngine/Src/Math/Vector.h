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
			Vector2 vec2;
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
			Vector3 vec3;
			struct {
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

	Vector2& Vector2View(float* data);

	Vector3& Vector3View(float* data);

	Vector4& Vector4View(float* data);
}