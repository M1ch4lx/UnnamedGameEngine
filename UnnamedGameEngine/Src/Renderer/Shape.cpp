#include "Pch.h"
#include "Shape.h"

namespace UEngine
{
	Shape::Shape(unsigned int verticesCount, unsigned int indicesCount,
		const std::initializer_list<unsigned int>& indices) :

		VerticesCount(verticesCount), IndicesCount(indicesCount),
		pattern(indices)
	{
		auto [minIndex, maxIndex]
			= std::minmax_element(pattern.begin(), pattern.end());
		
		if (*minIndex >= VerticesCount || *maxIndex >= VerticesCount
			|| pattern.size() != IndicesCount)
		{
			throw std::exception("Cannot create shape pattern");
		}
	}

	const std::vector<unsigned int>& Shape::Pattern() const
	{
		return pattern;
	}

	void Shape::IndexSingleShape(unsigned int* indices, unsigned int verticesOffset, unsigned int indicesOffset) const
	{
		for (unsigned int i = 0; i < IndicesCount; i++)
		{
			indices[i + indicesOffset] = pattern[i] + verticesOffset;
		}
	}

	void Shape::IndexShapes(unsigned int* indices, unsigned int verticesOffset, unsigned int count, unsigned int indicesOffset)
	{
		for (unsigned int i = 0; i < count; i++)
		{
			for (unsigned int j = 0; j < IndicesCount; j++)
			{
				indices[(i * IndicesCount) + j + indicesOffset]
					= pattern[j] + (i * VerticesCount) + verticesOffset;
			}
		}
	}
}