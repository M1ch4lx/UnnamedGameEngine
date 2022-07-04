#pragma once

#include "Vertex.h"

namespace UEngine
{
	class VertexBuffer
	{
	public:
		virtual ~VertexBuffer() = default;

		virtual void Bind() = 0;

		virtual void SetData(const void* data, size_t size) = 0;

		virtual void SetLayout(const VertexLayout* layout) = 0;
	};

	class IndexBuffer
	{
	public:
		virtual ~IndexBuffer() = default;

		virtual void Bind() const = 0;

		virtual size_t GetCount() const = 0;

		// void Init(uint32_t* indices, uint32_t count);
	};
}