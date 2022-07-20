#pragma once

#include "Renderer/Texture.h"

namespace UEngine
{
	class Sprite2D
	{
	private:
		static constexpr float DefaultPixelsPerUnit = 100.f;

		std::string name;

		Ref<Texture> texture;

		float pixelsPerUnit;

		Vector2 size;

		Rect boundingRect;

	public:
		Sprite2D(const std::string& name, const Ref<Texture>& texture);

		const std::string& Name() const;

		const Vector2& Size() const;

		const Ref<Texture>& GetTexture() const;

		float GetPixelsPerUnit() const;

		void SetPixelsPerUnit(float val);

		const Rect& GetBoundingRect() const;

	private:
		void CalculateDimensions();
	};
}