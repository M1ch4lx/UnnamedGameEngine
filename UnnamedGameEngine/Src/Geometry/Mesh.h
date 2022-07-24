#pragma once

#include "Core/Common.h"
#include "Core/FactoryObject.h"

#include "Renderer/Vertex.h"

namespace UEngine
{
	template<typename VertexType>
	class Mesh :public FactoryObject
	{
	private:
		std::vector<VertexType> vertices;

		std::vector<unsigned int> indices;

	public:
		Mesh(unsigned int verticesCount, unsigned int indicesCount)
		{
			vertices.resize(verticesCount);
			indices.resize(indicesCount);
		}

		void SetData(VertexType* data, unsigned int count)
		{
			if (count > vertices.size())
			{
				throw std::exception();
			}
			std::copy(data, data + count, vertices.data());
		}

		VertexType* GetVertices()
		{
			return vertices.data();
		}

		void SetIndices(unsigned int* data, unsigned int count)
		{
			if (count > indices.size())
			{
				throw std::exception();
			}
			std::copy(data, data + count, indices.data());
		}

		unsigned int* GetIndices()
		{
			return indices.data();
		}

		unsigned int VerticesCapacity() const
		{
			return vertices.size();
		}

		unsigned int IndicesCapacity() const
		{
			return indices.size();
		}
	};
}