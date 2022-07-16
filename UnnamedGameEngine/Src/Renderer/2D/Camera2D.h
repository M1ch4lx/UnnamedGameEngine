#pragma once

#include "Geometry/2D/Transformation2D.h"

#include "Renderer/Camera.h"

#include "Core/Common.h"

namespace UEngine
{
	class Camera2D :public Camera, public Transformable2D
	{
	private:
		static constexpr float SIZE_MULTIPLIER = 10.f;

		Viewport viewport;

		float size;

	public:
		Camera2D();

		const Viewport& GetViewport() const override;

		void SetViewport(const Viewport& viewport) override;

		void SetRatio(const Vector2& ratio) override;

		const Vector2& GetRatio() const override;

		void SetSize(float size) override;

		float GetSize() const override;

		Vector2 GetDimensions() const override;

		Matrix4 GetViewMatrix() const override;

		Matrix4 GetProjectionMatrix() const override;
	};
}