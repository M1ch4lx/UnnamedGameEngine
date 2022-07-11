#include "Pch.h"
#include "Matrices.h"

namespace UEngine
{
	Matrix4 IdentityMatrix()
	{
		Matrix4 mat;
		mat[0][0] = mat[1][1] = mat[2][2] = mat[3][3] = 1.f;
		return mat;
	}

	Matrix4 TranslationMatrix(const Vector3& translation)
	{
		Matrix4 mat = IdentityMatrix();
		mat[0][3] = translation.x;
		mat[1][3] = translation.y;
		mat[2][3] = translation.z;
		return mat;
	}

	Matrix4 RotationMatrixAroundZ(float angle)
	{
		Matrix4 mat = IdentityMatrix();
		mat[0][0] = std::cos(angle);
		mat[0][1] = -std::sin(angle);
		mat[1][0] = std::sin(angle);
		mat[1][1] = std::cos(angle);
		return mat;
	}

	Matrix4 ScaleMatrix(float kx, float ky, float kz)
	{
		Matrix4 mat = IdentityMatrix();
		mat[0][0] = kx;
		mat[1][1] = ky;
		mat[2][2] = kz;
		return mat;
	}

	Matrix4 ScaleMatrix(const Vector3& scale)
	{
		return ScaleMatrix(scale.x, scale.y, scale.z);
	}

	Matrix4 ModelMatrix(const Vector3& translation, const Vector3& scale, float angle)
	{
		return TranslationMatrix(translation) *
			(RotationMatrixAroundZ(angle) * ScaleMatrix(scale));
	}
}