#pragma once

#include "Geometry/Vertex.h"

#include "Renderer/Batch.h"

#include "Sprite.h"

namespace UEngine
{
	struct SpriteVertex
	{
		Vector3 ModelPosition;
		Vector3 Translation;
		Color3 Color;
		Vector2 TexCoord;

		SpriteVertex() = default;

		static const VertexLayout& Layout();
	};

	class SpriteInstance
	{
	private:
		const Ref<Sprite> sprite;

		SpriteVertex* vertices;

	public:
		SpriteInstance(SpriteVertex* data);
	};

	class SpriteBatch :public Batch
	{
	private:
		static constexpr unsigned int VerticesPerSprite = 4;
		static constexpr unsigned int IndicesPerSprite = 6;

		std::vector<Ref<Spritesheet>> spritesheets;

		std::vector<SpriteVertex> vertices;

		unsigned int indicesCount;

	public:
		SpriteBatch(unsigned int capacity);

		~SpriteBatch();

		const Ref<VertexArray>& GetVertexArray() const override;

		const Ref<Material>& GetMaterial() const override;
	};
}