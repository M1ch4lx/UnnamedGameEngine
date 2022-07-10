#include "Pch.h"
#include "OpenGLVertexBuffer.h"

namespace UEngine
{
	OpenGLVertexBuffer::OpenGLVertexBuffer() :
		id(0), size(0)
	{
		glGenBuffers(1, &id);
	}

	OpenGLVertexBuffer::~OpenGLVertexBuffer()
	{
		glDeleteBuffers(1, &id);
	}

	void OpenGLVertexBuffer::Bind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, id);
	}

	void OpenGLVertexBuffer::SetData(const void* vertecies, unsigned int verteciesCount, const VertexLayout& layout)
	{
		glBindBuffer(GL_ARRAY_BUFFER, id);
		this->layout = layout;
		auto dataSize = verteciesCount * layout.Stride();
		if (dataSize > size)
		{
			glBufferData(GL_ARRAY_BUFFER, dataSize, vertecies, GL_DYNAMIC_DRAW);

			size = dataSize;
			return;
		}
		glBufferSubData(GL_ARRAY_BUFFER, 0, dataSize, vertecies);
	}

	const VertexLayout& OpenGLVertexBuffer::GetLayout() const
	{
		return layout;
	}

	OpenGLIndexBuffer::OpenGLIndexBuffer(unsigned int* indices, unsigned int count) :
		id(0), count(count)
	{
		glGenBuffers(1, &id);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * count, indices, GL_STATIC_DRAW);
	}

	OpenGLIndexBuffer::~OpenGLIndexBuffer()
	{
		glDeleteBuffers(1, &id);
	}

	void OpenGLIndexBuffer::Bind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
	}

	unsigned int OpenGLIndexBuffer::GetCount() const
	{
		return count;
	}
}