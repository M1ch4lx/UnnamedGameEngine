#pragma once

#include "Matrix.h"

namespace UEngine
{
	namespace Math
	{
		Matrix4 Identity();

		Matrix4 Translation(const Vector3& translation);

		// Clockwise
		Matrix4 RotationAroundZ(float angle);

		Matrix4 Scale(float kx, float ky, float kz = 1.f);

		Matrix4 Scale(const Vector3& scale);

		Matrix4 Model(const Vector3& translation, const Vector3& scale, float rotation);

		Matrix4 View2D(const Vector2& cameraPosition, float rotation);

		Matrix4 Orthographic2D(const Vector2& cameraSize, float zNear, float zFar);
	}
}