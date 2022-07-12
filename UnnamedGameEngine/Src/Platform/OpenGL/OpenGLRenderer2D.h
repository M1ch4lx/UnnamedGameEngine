#pragma once

#include "OpenGLCommon.h"

#include "Renderer/Renderer2D.h"

namespace UEngine
{
	class OpenGLRenderer2D :public Renderer2D
	{
	private:
		RenderContext* context;

		Camera2D camera;

	public:
		OpenGLRenderer2D(RenderContext* context);

		virtual void BeginFrame() override;

		virtual void EndFrame() override;

		virtual void ClearScreen() override;

		virtual void ClearDepth() override;

		virtual void Render(const Ref<VertexArray>& vao) override;

		virtual void SetCamera(const Camera2D& camera) override;

		virtual const Camera2D& GetCamera() const override;

		virtual RenderContext* GetContext() const override;
	};
}