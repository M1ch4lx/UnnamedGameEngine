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

		void SetData(const float* data, unsigned int dataSize) override;

		void SetLayout(const VertexLayout& layout) override;

		const VertexLayout& GetLayout() const override;
	};

	class OpenGLIndexBuffer :public IndexBuffer
	{
	private:
		unsigned int id;

	public:
		OpenGLIndexBuffer();

		~OpenGLIndexBuffer();

		void Bind() const override;

		unsigned int GetCount() const override;

		void SetIndices(unsigned int* indices, unsigned int count) override;
	};
}