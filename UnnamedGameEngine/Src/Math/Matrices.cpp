#include "Pch.h"
#include "Matrices.h"

namespace UEngine
{
	namespace Math
	{
		Matrix4 Identity()
		{
			Matrix4 mat;
			mat[0][0] = mat[1][1] = mat[2][2] = mat[3][3] = 1.f;
			return mat;
		}

		Matrix4 Translation(const Vector3& translation)
		{
			Matrix4 mat = Identity();
			mat[0][3] = translation.x;
			mat[1][3] = translation.y;
			mat[2][3] = translation.z;
			return mat;
		}

		Matrix4 RotationAroundZ(float angle)
		{
			Matrix4 mat = Identity();
			mat[0][0] = std::cos(angle);
			mat[0][1] = std::sin(angle);
			mat[1][0] = -std::sin(angle);
			mat[1][1] = std::cos(angle);
			return mat;
		}

		Matrix4 Scale(float kx, float ky, float kz)
		{
			Matrix4 mat = Identity();
			mat[0][0] = kx;
			mat[1][1] = ky;
			mat[2][2] = kz;
			return mat;
		}

		Matrix4 Scale(const Vector3& scale)
		{
			return Scale(scale.x, scale.y, scale.z);
		}

		Matrix4 Model(const Vector3& translation, const Vector3& scale, float rotation)
		{
			return Translation(translation) *
				(RotationAroundZ(rotation) * Scale(scale));
		}

		Matrix4 View2D(const Vector2& cameraPosition, float rotation)
		{
			return RotationAroundZ(-rotation) *
				Translation(Vector(-cameraPosition.x, -cameraPosition.y, 0.f));
		}

		Matrix4 Orthographic2D(const Vector2& cameraSize, float zNear, float zFar)
		{
			return Scale(2.f / cameraSize.x, 2.f / cameraSize.y,
				2.f / (zFar - zNear)) * Translation(Vector(0.f, 0.f, -zNear));
		}
	}
}