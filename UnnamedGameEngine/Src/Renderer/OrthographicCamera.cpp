#include "Pch.h"
#include "OrthographicCamera.h"

namespace UEngine
{
	OrthographicCamera2D::OrthographicCamera2D() :
		size(6.f)
	{
		transformation.Scale = Vector(16.f, 9.f, 1.f);
	}

	const Viewport& OrthographicCamera2D::GetViewport() const
	{
		return viewport;
	}

	void OrthographicCamera2D::SetViewport(const Viewport& viewport)
	{
		this->viewport = viewport;
	}

	void OrthographicCamera2D::SetRatio(const Vector2& ratio)
	{
		transformation.Scale = Vector(ratio, 1.f);
	}

	const Vector2& OrthographicCamera2D::GetRatio() const
	{
		return transformation.Scale.xy;
	}

	void OrthographicCamera2D::SetSize(float size)
	{
		this->size = size;
	}

	float OrthographicCamera2D::GetSize() const
	{
		return size;
	}

	Vector2 OrthographicCamera2D::GetDimensions() const
	{
		return transformation.Scale.xy * (size * SIZE_MULTIPLIER);
	}

	Matrix4 OrthographicCamera2D::GetViewMatrix() const
	{
		return Math::View2D(transformation.Position.xy,
			Radians(transformation.Rotation.z));
	}

	Matrix4 OrthographicCamera2D::GetProjectionMatrix() const
	{
		return Math::Orthographic2D(GetDimensions(), 0.f, 100.f);
	}
}