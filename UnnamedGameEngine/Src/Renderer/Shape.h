#pragma once

#include <initializer_list>
#include <algorithm>

namespace UEngine
{
	class Shape
	{
	public:
		const unsigned int VerticesCount;

		const unsigned int IndicesCount;

	private:
		std::vector<unsigned int> pattern;

	public:
		Shape(unsigned int verticesCount, unsigned int indicesCount, const std::initializer_list<unsigned int>& indices);

		const std::vector<unsigned int>& Pattern() const;

		void IndexSingleShape(unsigned int* indices, unsigned int verticesOffset, unsigned int indicesOffset = 0) const;

		void IndexShapes(unsigned int* indices, unsigned int verticesOffset, unsigned int count, unsigned int indicesOffset = 0);
	};
}