#pragma once

#include "Renderer/VertexBuffer.h"

#include "OpenGLCommon.h"

namespace UEngine
{
	class OpenGLVertexBuffer :public VertexBuffer
	{
	private:
		unsigned int id;
		
		unsigned int size;

		VertexLayout layout;

	public:
		OpenGLVertexBuffer();

		~OpenGLVertexBuffer();

		void Bind() override;

		void SetData(const void* vertecies, unsigned int verteciesCount, const VertexLayout& layout) override;

		const VertexLayout& GetLayout() const override;
	};

	class OpenGLIndexBuffer :public IndexBuffer
	{
	private:
		unsigned int id;

		unsigned int count;

	public:
		OpenGLIndexBuffer(unsigned int* indices, unsigned int count);

		~OpenGLIndexBuffer();

		void Bind() const override;

		unsigned int GetCount() const override;
	};
}