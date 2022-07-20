#pragma once

#include "Core/FactoryObject.h"

#include "Geometry/Vertex.h"

namespace UEngine
{
	class VertexBuffer :public FactoryObject
	{
	public:
		virtual void Bind() = 0;

		virtual void SetData(const void* vertecies, unsigned int verticesCount, const VertexLayout& layout) = 0;

		virtual unsigned int GetCount() const = 0;

		virtual const VertexLayout& GetLayout() const = 0;
	};

	class IndexBuffer :public FactoryObject
	{
	public:
		virtual void Bind() = 0;

		virtual unsigned int GetCount() const = 0;
	};
}