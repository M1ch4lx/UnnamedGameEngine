#include "Pch.h"
#include "OpenGLTexture.h"

namespace UEngine
{
	OpenGLTexture::OpenGLTexture(const Image& image) :
		id(0), width(image.Width()), height(image.Height())
	{
		glGenTextures(1, &id);

		// RGBA internal format
		glTextureStorage2D(id, 0, GL_RGBA, width, height);

		glTextureParameteri(id, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(id, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTextureParameteri(id, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTextureParameteri(id, GL_TEXTURE_WRAP_T, GL_REPEAT);

		SetTextureData(image.Bpp(), image.Data());
	}

	OpenGLTexture::~OpenGLTexture()
	{
		glDeleteTextures(1, &id);
	}

	void OpenGLTexture::Bind(unsigned int slot)
	{
		glBindTextureUnit(slot, id);
	}

	void OpenGLTexture::SetTextureData(BPP dataFormat, const void* data)
	{
		unsigned int bpp = 0;
		switch (dataFormat)
		{
		case BPP::RGB:
			bpp = GL_RGB;
			break;

		case BPP::RGBA:
			bpp = GL_RGBA;
			break;

		default:
			throw std::exception("Format not supported");
			break;
		}

		glTextureSubImage2D(id, 0, 0, 0, width, height, bpp, GL_UNSIGNED_BYTE, data);
	}
}