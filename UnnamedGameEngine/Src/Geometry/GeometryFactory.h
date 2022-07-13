#pragma once

#include "Mesh.h"

namespace UEngine
{
	class GeometryFactory
	{
	public:
		template<typename VertexType>
		Ref<Mesh<VertexType>> CreateMesh(unsigned int verticesCount, unsigned int indicesCount)
		{
			return Ref<Mesh<VertexType>>(new Mesh<VertexType>(verticesCount, indicesCount));
		}
	};
}