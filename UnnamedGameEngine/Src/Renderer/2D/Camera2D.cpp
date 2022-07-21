#include "Pch.h"
#include "Camera2D.h"

namespace UEngine
{
	Camera2D::Camera2D() :
		size(1.f)
	{
		transformation.Scale = Vector(16.f, 9.f);
	}

	const Viewport& Camera2D::GetViewport() const
	{
		return viewport;
	}

	void Camera2D::SetViewport(const Viewport& viewport)
	{
		this->viewport = viewport;
	}

	void Camera2D::SetRatio(const Vector2& ratio)
	{
		transformation.Scale = ratio;
	}

	const Vector2& Camera2D::GetRatio() const
	{
		return transformation.Scale;
	}

	void Camera2D::SetSize(float size)
	{
		this->size = size;
	}

	float Camera2D::GetSize() const
	{
		return size;
	}

	Vector2 Camera2D::GetDimensions() const
	{
		return transformation.Scale * size;
	}

	Matrix4 Camera2D::GetViewMatrix() const
	{
		return Math::View2D(transformation.Position,
			Radians(transformation.Rotation));
	}

	Matrix4 Camera2D::GetProjectionMatrix() const
	{
		return Math::Orthographic2D(GetDimensions(), -1.f, 100.f);
	}
}