#pragma once

#include "Shader.h"

#include <vector>

namespace UEngine
{
	enum class VertexElementType
	{
		Float, Float2, Float3, Float4, None
	};

	size_t VertexElementTypeSize(VertexElementType elementType)
	{
		static constexpr size_t FloatSize = sizeof(float);
		static constexpr size_t IntSize = sizeof(int);

		switch (elementType)
		{
		case VertexElementType::Float: return FloatSize;
		case VertexElementType::Float2: return FloatSize * 2;
		case VertexElementType::Float3: return FloatSize * 3;
		case VertexElementType::Float4: return FloatSize * 4;
		}

		return 0;
	}

	size_t VertexElementTypeCount(VertexElementType elementType)
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

	struct VertexElement
	{
		VertexElementType type;
		size_t size;
		size_t offset;

		VertexElement() :
			type(VertexElementType::None),
			size(0), offset(0)
		{}

		VertexElement(VertexElementType type) :
			type(type), size(VertexElementTypeSize(type)), offset(0)
		{}
	};

	class VertexLayout
	{
	private:
		std::vector<VertexElement> elements;

		size_t stride;

		void BuildLayout();

	public:
		VertexLayout(std::initializer_list<VertexElementType> elementsList);

		const std::vector<VertexElement>& Elements() const;

		size_t Stride() const;
	};
}