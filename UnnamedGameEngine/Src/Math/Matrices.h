#pragma once

#include "Matrix.h"

namespace UEngine
{
	Matrix4 IdentityMatrix();

	Matrix4 TranslationMatrix(const Vector3& translation);

	Matrix4 RotationMatrixAroundZ(float angle);

	Matrix4 ScaleMatrix(float kx, float ky, float kz=1.f);
}