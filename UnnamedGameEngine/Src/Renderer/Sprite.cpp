#include "Pch.h"
#include "Sprite.h"

namespace UEngine
{
	Sprite::Sprite(const std::string& name, ISpritesheet* spritesheet, const Rect& texCoords) :
		name(name), spritesheet(spritesheet), textureCoords(texCoords)
	{
		CalculateDimensions();
	}

	const std::string& Sprite::Name() const
	{
		return name;
	}

	const Vector2& Sprite::GetSize() const
	{
		return size;
	}

	const Ref<Texture>& Sprite::GetTexture() const
	{
		return spritesheet->GetTexture();
	}

	Ref<BatchTexture>& Sprite::GetBatchTexture()
	{
		return spritesheet->GetBatchTexture();
	}

	const ISpritesheet* Sprite::GetSpritesheet() const
	{
		return spritesheet;
	}

	void Sprite::CalculateDimensions()
	{
		const auto [widthRatio, heightRatio] = textureCoords.Size();

		const auto& texture = spritesheet->GetTexture();

		size = UnitCordinates(spritesheet->GetPixelsPerUnit(), Vector(
			widthRatio * texture->Size().x,
			heightRatio * texture->Size().y
		));

		boundingRect = Rect(size);
	}

	const Rect& Sprite::GetBoundingRect() const
	{
		return boundingRect;
	}

	const Rect& Sprite::GetTextureCoords() const
	{
		return textureCoords;
	}

	Spritesheet::Spritesheet(const std::string& name, const Ref<Texture>& texture) :
		pixelsPerUnit(DefaultPixelsPerUnit), name(name), texture(texture),
		batchTexture(new BatchTexture(texture))
	{
		sprites.emplace_back(new Sprite(name + "_0", this, Rect(1.f, 0.f, 0.f, 1.f)));
	}

	const std::string& Spritesheet::Name() const
	{
		return name;
	}

	const Ref<Texture>& Spritesheet::GetTexture() const
	{
		return texture;
	}

	Ref<BatchTexture>& Spritesheet::GetBatchTexture()
	{
		return batchTexture;
	}

	float Spritesheet::GetPixelsPerUnit() const
	{
		return pixelsPerUnit;
	}

	void Spritesheet::SetPixelsPerUnit(float val)
	{
		pixelsPerUnit = val;
		for (auto& sprite : sprites)
		{
			sprite->CalculateDimensions();
		}
	}

	const std::vector<Ref<Sprite>>& Spritesheet::Sprites() const
	{
		return sprites;
	}
}