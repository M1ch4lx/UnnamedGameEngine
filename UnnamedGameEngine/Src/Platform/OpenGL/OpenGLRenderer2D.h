#pragma once

#include "OpenGLCommon.h"

#include "Renderer/2D/Renderer2D.h"

#include "Renderer/GraphicsFactory.h"

namespace UEngine
{
	class OpenGLRenderer2D :public Renderer2D
	{
	private:
		RenderContext* context;

		// ViewProjection matrix
		Matrix4 viewProjectionMatrix;

		Color3 clearColor;

		Ref<MaterialInstance> materialInstance;

		DenormalizedViewport viewport;

	public:
		OpenGLRenderer2D(RenderContext* context);

		void ClearScreen() override;

		void SetClearColor(const Color3& Color) override;

		const Color3& GetClearColor() const override;

		void ClearDepth() override;

		RenderContext* GetContext() const override;

		void BeginScene(const Camera2D& camera) override;

		void EndScene() override;

		void Display() override;

		void SetMaterial(const Ref<MaterialInstance>& materialInstance) override;

		void Render(const Ref<VertexArray>& vao, const Transformation2D& transform) override;

		void RenderRectangle(const Transformation2D& transform) override;

	private:
		void ApplyMaterialFlags();
	};
}