#include "Pch.h"
#include "OpenGLVertexBuffer.h"

namespace UEngine
{
	OpenGLVertexBuffer::OpenGLVertexBuffer() :
		id(0), count(0), usage(BufferUsage::Unspecified)
	{
		glCreateBuffers(1, &id);
	}

	OpenGLVertexBuffer::~OpenGLVertexBuffer()
	{
		glDeleteBuffers(1, &id);
	}

	void OpenGLVertexBuffer::Bind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, id);
	}

	void OpenGLVertexBuffer::SetVertices(const void* vertecies, unsigned int verticesCount, const VertexLayout& layout)
	{
		usage = BufferUsage::Dynamic;
		glBindBuffer(GL_ARRAY_BUFFER, id);
		this->layout = layout;
		auto dataSize = verticesCount * layout.Stride();
		if (verticesCount > count)
		{
			glBufferData(GL_ARRAY_BUFFER, dataSize, vertecies, GL_DYNAMIC_DRAW);

			count = verticesCount;

			return;
		}
		glBufferSubData(GL_ARRAY_BUFFER, 0, dataSize, vertecies);
	}

	void OpenGLVertexBuffer::SetStaticData(const void* vertecies, unsigned int verticesCount, const VertexLayout& layout)
	{
		usage = BufferUsage::Static;
		glBindBuffer(GL_ARRAY_BUFFER, id);
		this->layout = layout;
		auto dataSize = verticesCount * layout.Stride();

		glBufferData(GL_ARRAY_BUFFER, dataSize, vertecies, GL_STATIC_DRAW);
	}

	const VertexLayout& OpenGLVertexBuffer::GetLayout() const
	{
		return layout;
	}

	unsigned int OpenGLVertexBuffer::GetCount() const
	{
		return count;
	}

	BufferUsage OpenGLVertexBuffer::Usage() const
	{
		return usage;
	}

	OpenGLIndexBuffer::OpenGLIndexBuffer(unsigned int* indices, unsigned int count) :
		id(0), count(count)
	{
		glCreateBuffers(1, &id);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * count, indices, GL_STATIC_DRAW);
	}

	OpenGLIndexBuffer::~OpenGLIndexBuffer()
	{
		glDeleteBuffers(1, &id);
	}

	void OpenGLIndexBuffer::Bind()
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
	}

	unsigned int OpenGLIndexBuffer::GetCount() const
	{
		return count;
	}
}