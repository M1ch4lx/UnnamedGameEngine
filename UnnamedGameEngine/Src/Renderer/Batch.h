#pragma once

#include "Sprite.h"

namespace UEngine
{
	class ShapePattern
	{
		int i = 0;
	};

	class Batch
	{
	public:
		int i = 0;
		Batch() = default;
		//Batch(const VertexLayout& layout, unsigned int verticesCount, unsigned int indicesCount) {};
	};

	class StaticBatch
	{
	public:
		//StaticBatch(const VertexLayout& layout, unsigned int verticesCount, const ShapePattern& pattern) {};
	};

	class BatchTexture :public FactoryObject
	{
	private:
		Ref<Texture> texture;

		Batch* batch;

		unsigned int slot;

	public:
		BatchTexture(const Ref<Texture>& texture) :
			texture(texture), batch(nullptr), slot(0)
		{}

		std::tuple<Batch*, unsigned int> GetCurrentBatch() const
		{
			return { batch, slot };
		}

		void SetCurrentBatch(Batch* batch, unsigned int slot)
		{
			this->batch = batch;
			this->slot = slot;
		}

		const Ref<Texture>& GetTexture() const
		{
			return texture;
		}
	};
}