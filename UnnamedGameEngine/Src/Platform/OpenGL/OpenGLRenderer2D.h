#pragma once

#include "OpenGLCommon.h"

#include "Renderer/Renderer2D.h"

#include "Renderer/GraphicsFactory.h"

namespace UEngine
{
	class OpenGLRenderer2D :public Renderer2D
	{
	private:
		RenderContext* context;

		Renderer2DShaders shaders;
		
		// ViewProjection matrix
		Matrix4 viewProjectionMatrix;

		// Rectangle
		Ref<VertexArray> rectangleVao;
		void InitializeRectangleVao();

	public:
		OpenGLRenderer2D(RenderContext* context);

		void ClearScreen() override;

		void ClearDepth() override;

		RenderContext* GetContext() const override;

		Renderer2DShaders& ShadersConfiguration() override;

		void BeginScene(const OrthographicCamera2D& camera) override;

		void EndScene() override;

		void Display() override;

		void RenderRectangle(const Transformation& transform, const Color4& color) override;
	};
}