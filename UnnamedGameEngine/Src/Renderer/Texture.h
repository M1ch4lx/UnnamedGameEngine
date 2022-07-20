#pragma once

#include "Data/Image.h"

#include "Math/Math.h"

namespace UEngine
{
	enum class TextureWrap
	{
		Repeat, Clamp
	};

	enum class TextureFilter
	{
		Point, Linear
	};

	struct TextureSettings
	{
		TextureWrap WrapT;
		TextureWrap WrapS;
		TextureFilter FilterMin;
		TextureFilter FilterMag;

		TextureSettings() :
			WrapT(TextureWrap::Clamp), WrapS(TextureWrap::Clamp),
			FilterMin(TextureFilter::Linear), FilterMag(TextureFilter::Linear)
		{}
	};

	class Texture :public FactoryObject
	{
	public:
		virtual void Bind(unsigned int slot) = 0;

		virtual const Vector2& Size() const = 0;

		virtual void ApplySettings(const TextureSettings& settings) = 0;

		virtual const TextureSettings& GetSettings() const = 0;
	};
}