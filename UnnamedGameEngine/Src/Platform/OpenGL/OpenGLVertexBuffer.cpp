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

	void OpenGLVertexBuffer::SetData(const float* data, unsigned int dataSize)
	{
		glBindBuffer(GL_ARRAY_BUFFER, id);
		if (dataSize > size)
		{
			glBufferData(GL_ARRAY_BUFFER, dataSize,
				reinterpret_cast<const void*>(data), GL_DYNAMIC_DRAW);

			size = dataSize;
			return;
		}
		glBufferSubData(GL_ARRAY_BUFFER, 0, dataSize, reinterpret_cast<const void*>(data));
	}

	void OpenGLVertexBuffer::SetLayout(const VertexLayout& layout)
	{
		this->layout = layout;
	}

	const VertexLayout& OpenGLVertexBuffer::GetLayout() const
	{
		return layout;
	}

	OpenGLIndexBuffer::OpenGLIndexBuffer() :
		id(0)
	{

	}

	OpenGLIndexBuffer::~OpenGLIndexBuffer()
	{

	}

	void OpenGLIndexBuffer::Bind() const
	{

	}

	unsigned int OpenGLIndexBuffer::GetCount() const
	{
		return 0;
	}

	void OpenGLIndexBuffer::SetIndices(unsigned int* indices, unsigned int count)
	{

	}
}