#pragma once

#include "OpenGLCommon.h"

#include "Renderer/2D/Renderer2D.h"

#include "Renderer/GraphicsFactory.h"

namespace UEngine
{
	struct RectangleVertex
	{
		Vector3 ModelPosition;
		Vector2 Translation;
		float Rotation;
		Color4 Color;
		int TexSlot;
		Vector2 TexCoord;

		RectangleVertex() :
			TexSlot(0), Rotation(0.f)
		{}

		static const VertexLayout& Layout();
	};

	class OpenGLRenderer2D :public Renderer2D
	{
	private:
		static constexpr unsigned int NoTextureSlot = 32;

		RenderContext* context;

		// ViewProjection matrix
		Matrix4 viewProjectionMatrix;

		Color3 clearColor;

		DenormalizedViewport viewport;

		struct RectangleBatchData
		{
			Batch batch;

			Ref<MaterialInstance> MaterialInstance;

			Ref<VertexArray> Vao;

			Ref<VertexBuffer> Vbo;

			Ref<IndexBuffer> Ibo;

			std::vector<RectangleVertex> Vertices;

			const unsigned int RectanglesCapacity = 1000;

			const unsigned int MaxTextures = 16;

			unsigned int UsedVertices = 0;

			unsigned int UsedRectangles = 0;

			unsigned int UsedTextures = 0;

			std::vector<Ref<BatchTexture>> BatchTextures;

			std::vector<unsigned int> TextureSlots;

			RectangleBatchData();

		} rectangleBatch;

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

		void NextBatch(const Ref<MaterialInstance>& materialInstance) override;

		void RenderBatch() override;

		void RenderRectangle(const Transformation2D& transform, const Color4& color) override;

		void RenderSprite(const Transformation2D& transform, const Color4& color, const Ref<Sprite>& sprite) override;

	private:
		void ApplyMaterialFlags(const Ref<MaterialInstance>& materialInstance);
	};
}