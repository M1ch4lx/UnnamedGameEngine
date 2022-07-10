#include "Pch.h"
#include "Vertex.h"

namespace UEngine
{
	unsigned int VertexElementTypeSize(VertexElementType elementType)
	{
		static constexpr unsigned int FloatSize = sizeof(float);
		static constexpr unsigned int IntSize = sizeof(int);

		switch (elementType)
		{
		case VertexElementType::Float: return FloatSize;
		case VertexElementType::Float2: return FloatSize * 2;
		case VertexElementType::Float3: return FloatSize * 3;
		case VertexElementType::Float4: return FloatSize * 4;
		}

		return 0;
	}

	unsigned int VertexElementTypeCount(VertexElementType elementType)
	{
		switch (elementType)
		{
		case VertexElementType::Float: return 1;
		case VertexElementType::Float2: return 2;
		case VertexElementType::Float3: return 3;
		case VertexElementType::Float4: return 4;
		}

		return 0;
	}

	VertexLayout::VertexLayout() :
		stride(0)
	{

	}

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
		unsigned int offset = 0;
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

	unsigned int VertexLayout::Stride() const
	{
		return stride;
	}

	const VertexLayout& Vertex::Layout()
	{
		static const VertexLayout layout = { VertexElementType::Float3 };
		return layout;
	}
}