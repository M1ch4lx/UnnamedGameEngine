#pragma once

#include <vector>

#include "Math/Vector.h"

namespace UEngine
{
	enum class VertexElementType
	{
		Float, Float2, Float3, Float4, None
	};

	unsigned int VertexElementTypeSize(VertexElementType elementType);

	unsigned int VertexElementTypeCount(VertexElementType elementType);

	struct VertexElement
	{
		VertexElementType type;
		unsigned int size;
		unsigned int offset;
		unsigned int count;

		VertexElement() :
			type(VertexElementType::None),
			size(0), offset(0), count(0)
		{}

		VertexElement(VertexElementType type) :
			type(type), size(VertexElementTypeSize(type)),
			offset(0), count(VertexElementTypeCount(type))
		{}
	};

	class VertexLayout
	{
	private:
		std::vector<VertexElement> elements;

		unsigned int stride;

		void BuildLayout();

	public:
		VertexLayout();

		VertexLayout(std::initializer_list<VertexElementType> elementsList);

		const std::vector<VertexElement>& Elements() const;

		unsigned int Stride() const;
	};

	struct Vertex
	{
		Vector3 position;

		Vertex() = default;

		Vertex(const Vector3& position) :
			position(position)
		{}

		Vertex(float x, float y, float z) :
			position(x, y, z)
		{}

		static const VertexLayout& Layout();
	};
}