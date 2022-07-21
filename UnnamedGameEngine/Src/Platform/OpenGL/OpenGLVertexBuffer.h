#pragma once

#include "Renderer/VertexBuffer.h"

#include "OpenGLCommon.h"

namespace UEngine
{
	class OpenGLVertexBuffer :public VertexBuffer
	{
	private:
		unsigned int id;

		unsigned int count;

		VertexLayout layout;

		BufferUsage usage;

	public:
		OpenGLVertexBuffer();

		~OpenGLVertexBuffer();

		void Bind() override;

		void SetVertices(const void* vertecies, unsigned int verticesCount, const VertexLayout& layout) override;

		void SetStaticData(const void* vertecies, unsigned int verticesCount, const VertexLayout& layout) override;

		const VertexLayout& GetLayout() const override;

		unsigned int GetCount() const override;

		BufferUsage Usage() const override;
	};

	class OpenGLIndexBuffer :public IndexBuffer
	{
	private:
		unsigned int id;

		unsigned int count;

	public:
		OpenGLIndexBuffer(unsigned int* indices, unsigned int count);

		~OpenGLIndexBuffer();

		void Bind() override;

		unsigned int GetCount() const override;
	};
}