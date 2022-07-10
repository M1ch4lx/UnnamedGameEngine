#pragma once

#include "GraphicsObject.h"

#include "Geometry/Vertex.h"

namespace UEngine
{
	class VertexBuffer :public GraphicsObject
	{
	public:
		virtual void Bind() = 0;

		virtual void SetData(const void* vertecies, unsigned int verteciesCount, const VertexLayout& layout) = 0;

		virtual const VertexLayout& GetLayout() const = 0;
	};

	class IndexBuffer :public GraphicsObject
	{
	public:
		virtual void Bind() const = 0;

		virtual unsigned int GetCount() const = 0;
	};
}