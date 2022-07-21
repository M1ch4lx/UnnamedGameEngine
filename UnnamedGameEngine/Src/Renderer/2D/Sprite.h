#pragma once

#include "Renderer/Texture.h"

namespace UEngine
{
	class Spritesheet;

	class Sprite
	{
		friend class Spritesheet;
	private:
		const std::string name;

		const Ref<Texture> texture;

		const Rect textureCoords;

		Rect boundingRect;

		Vector2 size;

	public:
		Sprite(const std::string& name, const Ref<Texture>& texture, const Rect& texCoords);

		const std::string& Name() const;

		const Vector2& GetSize() const;

		const Rect& GetBoundingRect() const;

		const Rect& GetTextureCoords() const;

		const Ref<Texture>& GetTexture() const;
	};

	class Spritesheet
	{
	private:
		static constexpr float DefaultPixelsPerUnit = 100.f;

		const std::string name;

		const Ref<Texture> texture;

		float pixelsPerUnit;

		std::vector<Ref<Sprite>> sprites;

	public:
		Spritesheet(const std::string& name, const Ref<Texture>& texture);

		const Ref<Texture>& GetTexture() const;

		float GetPixelsPerUnit() const;

		void SetPixelsPerUnit(float val);

		const std::vector<Ref<Sprite>>& Sprites() const;

	private:
		void CalculateSpriteDimensions(const Ref<Sprite>& sprite);
	};
}