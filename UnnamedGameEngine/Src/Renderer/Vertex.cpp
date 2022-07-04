#include "Pch.h"
#include "Vertex.h"

namespace UEngine
{
	VertexLayout::VertexLayout(std::initializer_list<VertexElementType> elementsList) :
		stride(0)
	{
		elements.reserve(elementsList.size());

		for (auto elementType : elementsList)
		{
			elements.emplace_back(elementType);
		}

		BuildLayout();
	}

	void VertexLayout::BuildLayout()
	{
		size_t offset = 0;
		for (auto& element : elements)
		{
			element.offset = offset;
			offset += element.size;
		}
		stride = offset;
	}

	const std::vector<VertexElement>& VertexLayout::Elements() const
	{
		return elements;
	}

	size_t VertexLayout::Stride() const
	{
		return stride;
	}
}