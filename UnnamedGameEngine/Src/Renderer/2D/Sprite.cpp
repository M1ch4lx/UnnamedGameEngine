#include "Pch.h"
#include "Sprite.h"

namespace UEngine
{
	Sprite::Sprite(const std::string& name, const Ref<Texture>& texture, const Rect& texCoords) :
		name(name), texture(texture), textureCoords(texCoords)
	{
		
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
		return texture;
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
		pixelsPerUnit(DefaultPixelsPerUnit), name(name), texture(texture)
	{
		sprites.emplace_back(new Sprite(name + "_0", texture, Rect(1.f, 0.f, 0.f, 1.f)));

		CalculateSpriteDimensions(sprites.front());
	}

	const Ref<Texture>& Spritesheet::GetTexture() const
	{
		return texture;
	}

	float Spritesheet::GetPixelsPerUnit() const
	{
		return pixelsPerUnit;
	}

	void Spritesheet::SetPixelsPerUnit(float val)
	{
		pixelsPerUnit = val;
	}

	const std::vector<Ref<Sprite>>& Spritesheet::Sprites() const
	{
		return sprites;
	}

	void Spritesheet::CalculateSpriteDimensions(const Ref<Sprite>& sprite)
	{
		const auto [widthRatio, heightRatio] = sprite->textureCoords.Size();

		sprite->size = UnitCordinates(pixelsPerUnit, Vector(
			widthRatio * texture->Size().x,
			heightRatio * texture->Size().y
		));

		sprite->boundingRect = Rect(sprite->size);
	}
}