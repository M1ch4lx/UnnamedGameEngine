#pragma once

#include "Camera.h"

#include "Core/Common.h"

namespace UEngine
{
	class OrthographicCamera2D :public Camera
	{
	private:
		static constexpr float SIZE_MULTIPLIER = 10.f;

		Viewport viewport;

		float size;

	public:
		OrthographicCamera2D();

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