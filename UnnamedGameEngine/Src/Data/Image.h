#pragma once

#include "Core/Core.h"

#include "Vendor/stb/stb_image.h"

namespace UEngine
{
	enum class BPP
	{
		RGB = 3,
		RGBA = 4,
		None = 0
	};

	class Image :public FactoryObject
	{
	private:
		unsigned char* pixels;

		int width;
		int height;
		int bpp;

	public:
		Image();

		~Image();

		void LoadFromFile(const std::string& path, BPP desiredBpp = BPP::RGBA);

		void Clear();

		BPP Bpp() const;

		int Width() const;

		int Height() const;

		unsigned char* Data() const;
	};
}