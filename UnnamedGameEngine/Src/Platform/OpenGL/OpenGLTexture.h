#pragma once

#include "OpenGLCommon.h"

#include "Renderer/Texture.h"

namespace UEngine
{
	class OpenGLTexture :public Texture
	{
	private:
		unsigned int id;

		Vector2 size;

		TextureSettings settings;
		
	public:
		OpenGLTexture(const Image& image);

		~OpenGLTexture();

		void Bind(unsigned int slot) override;

		const Vector2& Size() const override;

		void ApplySettings(const TextureSettings& settings) override;

		const TextureSettings& GetSettings() const override;
	};
}