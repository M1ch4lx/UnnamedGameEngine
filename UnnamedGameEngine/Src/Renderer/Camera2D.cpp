#include "Pch.h"
#include "Camera2D.h"

namespace UEngine
{
	Camera2D::Camera2D() :
		size(6.f)
	{
		transformation.scale = Vector(16.f, 9.f);
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
		transformation.scale = ratio;
	}

	const Vector2& Camera2D::GetRatio() const
	{
		return transformation.scale;
	}

	void Camera2D::SetSize(float size)
	{
		this->size = size;
	}

	float Camera2D::GetSize() const
	{
		return size;
	}

	Vector2 Camera2D::CalculateSize() const
	{
		return transformation.scale * (size * SIZE_MULTIPLIER);
	}
}