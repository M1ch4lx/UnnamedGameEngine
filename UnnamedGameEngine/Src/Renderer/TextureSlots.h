#pragma once

#include "Sprite.h"

namespace UEngine
{
	class TextureSlotsBuffer :public FactoryObject
	{
	public:
		static constexpr unsigned int InvalidTextureSlot = 32;

	private:
		std::vector<Ref<Texture>> textures;

		std::array<unsigned int, 32> slots;

		std::unordered_map<Texture*, unsigned int> texturesSlots;

		unsigned int usedSlots;

		const unsigned int availableSlots;

	public:
		TextureSlotsBuffer();

		unsigned int AddTexture(const Ref<Texture>& texture);

		void ClearTextures();

		void BindTextures();

		std::tuple<const unsigned int*, unsigned int> SlotsUsage() const;
	};
}