#pragma once

#include "Vector.h"

#include <cassert>

namespace UEngine
{
	class Matrix4
	{
	public:
		static constexpr size_t Rows = 4;
		static constexpr size_t Cols = 4;

	private:
		float m[Rows][Cols];

	public:
		Matrix4();

		Matrix4(const Matrix4& mat);
		Matrix4(Matrix4&& mat);
		Matrix4& operator=(const Matrix4& mat);
		Matrix4& operator=(Matrix4&& mat);

		float* operator[](size_t index);

		const float* operator[](size_t index) const;

		const float* ConstData() const;

		float* Data();

		Matrix4 operator+(const Matrix4& mat) const;

		Matrix4 operator-(const Matrix4& mat) const;

		Matrix4 operator*(float scalar) const;

		Matrix4 operator*(const Matrix4& mat) const;

		Vector4 operator*(const Vector4& v) const;

		Matrix4 Transposed() const;

		void Transpose();

		void SetRow(size_t index, const Vector4& v);

		void SetColumn(size_t index, const Vector4& v);

		Vector4& Row(size_t index);
	};
};