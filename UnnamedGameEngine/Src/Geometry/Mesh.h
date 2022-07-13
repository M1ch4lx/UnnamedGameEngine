#pragma once

#include "Core/Common.h"
#include "Core/FactoryObject.h"

#include "Vertex.h"

namespace UEngine
{
	template<typename VertexType>
	class Mesh :public FactoryObject
	{
	private:
		VertexLayout layout;

		std::vector<VertexType> vertices;

		std::vector<unsigned int> indices;

	public:
		Mesh(unsigned int verticesCount, unsigned int indicesCount)
		{
			vertices.resize(verticesCount);

			indices.resize(indicesCount);
		}

		unsigned int VerticesCount() const
		{
			vertices.size();
		}

		unsigned int IndicesCount() const
		{
			indices.size();
		}

		const std::vector<VertexType>& Vertices()
		{
			return vertices;
		}

		const std::vector<unsigned int>& Indices()
		{
			return indices;
		}

		const VertexType* VerticesData() const
		{
			return vertices.data();
		}

		const unsigned int* IndicesData() const
		{
			return indices.data();
		}

		void SetVertices(VertexType* data, unsigned int count, unsigned int offset = 0)
		{
			if ((count + offset) > vertices.size())
			{
				throw std::exception("Mesh: cannot set vertices");
			}
			std::copy(data, data + count, vertices.begin() + offset);
		}

		void SetIndices(unsigned int* data, unsigned int count, unsigned int offset = 0)
		{
			if ((count + offset) > indices.size())
			{
				throw std::exception("Mesh: cannot set indices");
			}
			std::copy(data, data + count, indices.begin() + offset);
		}
	};
}