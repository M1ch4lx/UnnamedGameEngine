#include "Pch.h"
#include "OpenGLVertexArray.h"

namespace UEngine
{
	OpenGLVertexArray::OpenGLVertexArray(const Ref<VertexBuffer>& vertexBuffer, const Ref<IndexBuffer>& indexBuffer)
	{
		glGenVertexArrays(1, &id);

		glBindVertexArray(id);

		SetVertexBuffer(vertexBuffer);
		SetIndexBuffer(indexBuffer);
	}

	OpenGLVertexArray::~OpenGLVertexArray()
	{
		glDeleteVertexArrays(1, &id);
	}

	void OpenGLVertexArray::SetVertexBuffer(const Ref<VertexBuffer>& buffer)
	{
		if (!buffer)
		{
			return;
		}

		vertexBuffer = buffer;

		vertexBuffer->Bind();

		const auto& layout = vertexBuffer->GetLayout();
		unsigned int attribIndex = 0;

		for (const auto& element : layout.Elements())
		{
			glVertexAttribPointer(attribIndex, element.count, GL_FLOAT,
				GL_FALSE, element.size, (const void*)element.offset);

			glEnableVertexAttribArray(attribIndex);

			attribIndex++;
		}
	}

	void OpenGLVertexArray::SetIndexBuffer(const Ref<IndexBuffer>& buffer)
	{
		if (!buffer)
		{
			return;
		}

		indexBuffer = buffer;

		buffer->Bind();
	}

	void OpenGLVertexArray::Bind()
	{
		glBindVertexArray(id);
	}
}