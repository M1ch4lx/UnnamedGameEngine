#include "Pch.h"
#include "TextureSlots.h"

namespace UEngine
{
	TextureSlotsBuffer::TextureSlotsBuffer() :
		usedSlots(0), availableSlots(16)
	{
		textures.reserve(availableSlots);

		for (unsigned int i = 0; i < availableSlots; i++)
		{
			slots[i] = i;
		}
	}

	unsigned int TextureSlotsBuffer::AddTexture(const Ref<Texture>& texture)
	{
		auto iter = texturesSlots.find(texture.get());

		if (iter == texturesSlots.end())
		{
			iter = texturesSlots.insert(
				std::make_pair(texture.get(), InvalidTextureSlot)).first;
		}

		if (iter->second == InvalidTextureSlot)
		{
			if (usedSlots == availableSlots)
			{
				return InvalidTextureSlot;
			}

			textures.push_back(texture);
			iter->second = slots[usedSlots++];
		}

		return iter->second;
	}

	void TextureSlotsBuffer::ClearTextures()
	{
		textures.clear();

		for (auto& pair : texturesSlots)
		{
			pair.second = InvalidTextureSlot;
		}

		usedSlots = 0;
	}

	void TextureSlotsBuffer::BindTextures()
	{
		for (unsigned int i = 0; i < usedSlots; i++)
		{
			textures[i]->Bind(slots[i]);
		}
	}

	std::tuple<const unsigned int*, unsigned int> TextureSlotsBuffer::SlotsUsage() const
	{
		return { slots.data(), usedSlots };
	}
}