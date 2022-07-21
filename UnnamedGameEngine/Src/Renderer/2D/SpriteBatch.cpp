#include "Pch.h"
#include "SpriteBatch.h"

namespace UEngine
{
	const VertexLayout& SpriteVertex::Layout()
	{
		static const VertexLayout layout = {
			VertexElementType::Float3,
			VertexElementType::Float3,
			VertexElementType::Float3,
			VertexElementType::Float2
		};
		return layout;
	}

	SpriteBatch::SpriteBatch(unsigned int capacity) :
		indicesCount(capacity * 6)
	{
		vertices.resize(capacity * 4);
	}

	SpriteBatch::~SpriteBatch()
	{

	}

	const Ref<VertexArray>& SpriteBatch::GetVertexArray() const
	{
		
	}

	const Ref<Material>& SpriteBatch::GetMaterial() const
	{
		
	}
}