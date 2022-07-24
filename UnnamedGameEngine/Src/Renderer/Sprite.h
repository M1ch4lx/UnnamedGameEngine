#pragma once

#include "Renderer/Texture.h"

#include "Batch.h"

namespace UEngine
{
	class ISpritesheet :public FactoryObject
	{
	public:
		virtual const Ref<Texture>& GetTexture() const = 0;

		virtual Ref<BatchTexture>& GetBatchTexture() = 0;

		virtual const std::string& Name() const = 0;

		virtual float GetPixelsPerUnit() const = 0;

		virtual void SetPixelsPerUnit(float pixelsPerUnit) = 0;
	};

	class Sprite :public FactoryObject
	{
		friend class Spritesheet;
	private:
		ISpritesheet* spritesheet;

		const std::string name;

		const Rect textureCoords;

		Rect boundingRect;

		Vector2 size;

	public:
		Sprite(const std::string& name, ISpritesheet* spritesheet, const Rect& texCoords);

		const std::string& Name() const;

		const Vector2& GetSize() const;

		const Rect& GetBoundingRect() const;

		const Rect& GetTextureCoords() const;

		const Ref<Texture>& GetTexture() const;

		Ref<BatchTexture>& GetBatchTexture();

		const ISpritesheet* GetSpritesheet() const;

	private:
		void CalculateDimensions();
	};

	class Spritesheet :public ISpritesheet
	{
	private:
		static constexpr float DefaultPixelsPerUnit = 100.f;

		const std::string name;

		const Ref<Texture> texture;

		float pixelsPerUnit;

		std::vector<Ref<Sprite>> sprites;

		Ref<BatchTexture> batchTexture;

	public:
		Spritesheet(const std::string& name, const Ref<Texture>& texture);

		const std::string& Name() const override;

		const Ref<Texture>& GetTexture() const override;

		Ref<BatchTexture>& GetBatchTexture() override;

		float GetPixelsPerUnit() const override;

		void SetPixelsPerUnit(float val) override;

		const std::vector<Ref<Sprite>>& Sprites() const;
	};
}