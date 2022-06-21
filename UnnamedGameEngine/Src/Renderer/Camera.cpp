#include "Pch.h"
#include "Camera.h"

namespace UEngine
{
	Camera::Camera() :
		ratio(16.f, 9.f), size(6.f)
	{}

	const Viewport& Camera::GetViewport() const
	{
		return viewport;
	}

	void Camera::SetViewport(const Viewport& viewport)
	{
		this->viewport = viewport;
	}

	void Camera::SetRatio(const Vector2& ratio)
	{
		this->ratio = ratio;
	}

	const Vector2& Camera::GetRatio() const
	{
		return ratio;
	}

	void Camera::SetSize(float size)
	{
		this->size = size;
	}

	float Camera::GetSize() const
	{
		return size;
	}

	Vector2 Camera::CalculateSize() const
	{
		return ratio * (size * SIZE_MULTIPLIER);
	}
}