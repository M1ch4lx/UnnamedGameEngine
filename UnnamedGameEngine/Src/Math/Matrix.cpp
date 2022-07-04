#include "Pch.h"
#include "Matrix.h"

namespace UEngine
{
	Matrix4::Matrix4() :
		m{0.f}
	{}

	Matrix4::Matrix4(const Matrix4& mat) :
		m{0.f}
	{
		std::copy(mat.m[0], mat.m[0] + (Rows * Cols), m[0]);
	}

	Matrix4::Matrix4(Matrix4&& mat)
	{
		std::copy(mat.m[0], mat.m[0] + (Rows * Cols), m[0]);
	}

	Matrix4& Matrix4::operator=(const Matrix4& mat)
	{
		std::copy(mat.m[0], mat.m[0] + (Rows * Cols), m[0]);
		return *this;
	}

	Matrix4& Matrix4::operator=(Matrix4&& mat)
	{
		std::copy(mat.m[0], mat.m[0] + (Rows * Cols), m[0]);
		return *this;
	}

	float* Matrix4::operator[](size_t index)
	{
		assert(index < Rows);
		return m[index];
	}

	const float* Matrix4::operator[](size_t index) const
	{
		assert(index < Rows);
		return m[index];
	}

	float* Matrix4::Data()
	{
		return reinterpret_cast<float*>(m);
	}

	Matrix4 Matrix4::operator+(const Matrix4& mat) const
	{
		Matrix4 res;

		for (size_t i = 0; i < Rows; i++)
		{
			for (size_t j = 0; j < Cols; j++)
			{
				res.m[i][j] = m[i][j] + mat.m[i][j];
			}
		}

		return res;
	}

	Matrix4 Matrix4::operator-(const Matrix4& mat) const
	{
		Matrix4 res;

		for (size_t i = 0; i < Rows; i++)
		{
			for (size_t j = 0; j < Cols; j++)
			{
				res.m[i][j] = m[i][j] - mat.m[i][j];
			}
		}

		return res;
	}

	Matrix4 Matrix4::operator*(float scalar) const
	{
		Matrix4 res;

		for (size_t i = 0; i < Rows; i++)
		{
			for (size_t j = 0; j < Cols; j++)
			{
				res.m[i][j] *= scalar;
			}
		}

		return res;
	}

	Matrix4 Matrix4::operator*(const Matrix4& mat) const
	{
		Matrix4 matTransposed = mat.Transposed();
		Matrix4 product;
		for (size_t i = 0; i < Rows; i++)
		{
			product.SetColumn(i, *this * matTransposed.Row(i));
		}
		return product;
	}

	Vector4 Matrix4::operator*(const Vector4& v) const
	{
		return Vector4(
			(v.x * m[0][0]) + (v.y * m[0][1]) + (v.z * m[0][2]) + (v.w * m[0][3]),
			(v.x * m[1][0]) + (v.y * m[1][1]) + (v.z * m[1][2]) + (v.w * m[1][3]),
			(v.x * m[2][0]) + (v.y * m[2][1]) + (v.z * m[2][2]) + (v.w * m[2][3]),
			(v.x * m[3][0]) + (v.y * m[3][1]) + (v.z * m[3][2]) + (v.w * m[3][3])
		);
	}

	Matrix4 Matrix4::Transposed() const
	{
		Matrix4 transposed;
		for (size_t i = 0; i < Rows; i++)
		{
			for (size_t j = 0; j < Cols; j++)
			{
				transposed[j][i] = m[i][j];
			}
		}
		return transposed;
	}

	void Matrix4::Transpose()
	{
		*this = Transposed();
	}

	void Matrix4::SetRow(size_t index, const Vector4& v)
	{
		assert(index < Rows);
		std::copy(&v.x, &v.x + 4, m[0]);
	}

	void Matrix4::SetColumn(size_t index, const Vector4& v)
	{
		assert(index < Cols);
		m[0][index] = v.x;
		m[1][index] = v.y;
		m[2][index] = v.z;
		m[3][index] = v.w;
	}
	Vector4& Matrix4::Row(size_t index)
	{
		assert(index < Rows);
		return Vector4View(m[index]);
	}
}