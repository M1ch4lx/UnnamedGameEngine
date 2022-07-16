#pragma once

#include "OpenGLCommon.h"

#include "Renderer/Texture.h"

namespace UEngine
{
	class OpenGLTexture :public Texture
	{
	private:
		unsigned int id;

		int width;
		int height;
		
	public:
		OpenGLTexture(const Image& image);

		~OpenGLTexture();

		void Bind(unsigned int slot) override;

	private:
		void SetTextureData(BPP dataFormat, const void* data);
	};
}