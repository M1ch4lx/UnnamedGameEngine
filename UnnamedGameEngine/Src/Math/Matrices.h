#pragma once

#include "Matrix.h"

namespace UEngine
{
	Matrix4 IdentityMatrix();

	Matrix4 TranslationMatrix(const Vector3& translation);

	Matrix4 RotationMatrixAroundZ(float angle);

	Matrix4 ScaleMatrix(float kx, float ky, float kz=1.f);

	Matrix4 ScaleMatrix(const Vector3& scale);

	Matrix4 ModelMatrix(const Vector3& translation, const Vector3& scale, float angle);
}