#include "Pch.h"
#include "Sprite2D.h"

namespace UEngine
{
	Sprite2D::Sprite2D(const std::string& name, const Ref<Texture>& texture) :
		name(name), texture(texture), pixelsPerUnit(DefaultPixelsPerUnit)
	{
		CalculateDimensions();
	}

	const std::string& Sprite2D::Name() const
	{
		return name;
	}

	const Vector2& Sprite2D::Size() const
	{
		return size;
	}

	const Ref<Texture>& Sprite2D::GetTexture() const
	{
		return texture;
	}

	float Sprite2D::GetPixelsPerUnit() const
	{
		return pixelsPerUnit;
	}

	void Sprite2D::SetPixelsPerUnit(float val)
	{
		pixelsPerUnit = val;
		CalculateDimensions();
	}

	const Rect& Sprite2D::GetBoundingRect() const
	{
		return boundingRect;
	}

	void Sprite2D::CalculateDimensions()
	{
		size = UnitCordinates(pixelsPerUnit, texture->Size());
		boundingRect = Rect(size);
	}
}