#pragma once

#include "Core/Common.h"
#include "Core/FactoryObject.h"

#include "Vertex.h"

namespace UEngine
{
	template<typename VertexType>
	class StaticMesh
	{
	private:
		std::vector<VertexType> vertices;
	};
}