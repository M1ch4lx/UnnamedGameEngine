#include "Pch.h"
#include "OpenGLTexture.h"

namespace UEngine
{
	static GLenum GetGLWrapMode(TextureWrap wrap)
	{
		switch (wrap)
		{
		case TextureWrap::Clamp: return GL_CLAMP_TO_EDGE;

		case TextureWrap::Repeat: return GL_REPEAT;
		}

		throw std::exception("Texture wrap mode not supported");
	}

	static GLenum GetGLFilter(TextureFilter filter)
	{
		switch (filter)
		{
		case TextureFilter::Point: return GL_NEAREST;

		case TextureFilter::Linear: return GL_LINEAR;
		}

		throw std::exception("Texture filter not supported");
	}

	static std::tuple<GLenum, GLenum> GetGLFormat(BPP imageFormat)
	{
		switch (imageFormat)
		{
		case BPP::RGB: return { GL_RGB8, GL_RGB };

		case BPP::RGBA: return { GL_RGBA8, GL_RGBA };
		}

		throw std::exception("Pixel format not supported");
	}

	OpenGLTexture::OpenGLTexture(const Image& image) :
		id(0),
		size(static_cast<float>(image.Width()), static_cast<float>(image.Height()))
	{
		auto [internalFormat, dataFormat] = GetGLFormat(image.Bpp());

		glCreateTextures(GL_TEXTURE_2D, 1, &id);

		glTextureStorage2D(id, 1, internalFormat, image.Width(), image.Height());

		ApplySettings(settings);

		glTextureSubImage2D(id, 0, 0, 0, image.Width(), image.Height(), dataFormat, GL_UNSIGNED_BYTE, image.Data());
	}

	OpenGLTexture::~OpenGLTexture()
	{
		glDeleteTextures(1, &id);
	}

	void OpenGLTexture::Bind(unsigned int slot)
	{
		// TODO: reduce redundant bindings
		glBindTextureUnit(slot, id);
	}

	const Vector2& OpenGLTexture::Size() const
	{
		return size;
	}

	void OpenGLTexture::ApplySettings(const TextureSettings& settings)
	{
		glTextureParameteri(id, GL_TEXTURE_MIN_FILTER, GetGLFilter(settings.FilterMin));
		glTextureParameteri(id, GL_TEXTURE_MAG_FILTER, GetGLFilter(settings.FilterMag));

		glTextureParameteri(id, GL_TEXTURE_WRAP_S, GetGLWrapMode(settings.WrapS));
		glTextureParameteri(id, GL_TEXTURE_WRAP_T, GetGLWrapMode(settings.WrapT));

		this->settings = settings;
	}

	const TextureSettings& OpenGLTexture::GetSettings() const
	{
		return settings;
	}
}