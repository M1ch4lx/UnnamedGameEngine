#include "Pch.h"
#include "Image.h"

namespace UEngine
{
	Image::Image() :
		pixels(nullptr), width(0), height(0), bpp(0)
	{

	}

	Image::~Image()
	{
		Clear();
	}

	void Image::LoadFromFile(const std::string& path, BPP desiredBpp)
	{
		Clear();

		pixels = stbi_load(path.c_str(), &width,
			&height, &bpp, static_cast<int>(desiredBpp));
	}

	void Image::Clear()
	{
		if (pixels)
		{
			stbi_image_free(pixels);
			pixels = nullptr;

			width = 0;
			height = 0;
			bpp = 0;
		}
	}

	BPP Image::Bpp() const
	{
		return static_cast<BPP>(bpp);
	}

	int Image::Width() const
	{
		return width;
	}

	int Image::Height() const
	{
		return height;
	}

	unsigned char* Image::Data() const
	{
		return pixels;
	}
}