#pragma once

#include <vector>

#include "Math/Vector.h"

namespace UEngine
{
	enum class VertexElementType
	{
		Float, Float2, Float3, Float4,
		Int,
		None
	};

	unsigned int VertexElementTypeSize(VertexElementType elementType);

	unsigned int VertexElementTypeCount(VertexElementType elementType);

	struct VertexElement
	{
		VertexElementType Type;
		unsigned int Size;
		unsigned int Offset;
		unsigned int Count;

		VertexElement() :
			Type(VertexElementType::None),
			Size(0), Offset(0), Count(0)
		{}

		VertexElement(VertexElementType type) :
			Type(type), Size(VertexElementTypeSize(type)),
			Offset(0), Count(VertexElementTypeCount(type))
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
		Vector3 Position;

		Vertex() = default;

		Vertex(const Vector3& Position) :
			Position(Position)
		{}

		Vertex(float x, float y, float z) :
			Position(x, y, z)
		{}

		static const VertexLayout& Layout();
	};
}