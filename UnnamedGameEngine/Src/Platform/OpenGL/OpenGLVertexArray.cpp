#include "Pch.h"
#include "OpenGLVertexArray.h"

namespace UEngine
{
	OpenGLVertexArray::OpenGLVertexArray(const Ref<VertexBuffer>& vertexBuffer, const Ref<IndexBuffer>& indexBuffer)
	{
		glCreateVertexArrays(1, &id);

		glBindVertexArray(id);

		SetVertexBuffer(vertexBuffer);
		SetIndexBuffer(indexBuffer);

		glBindVertexArray(0);
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
			glVertexAttribPointer(attribIndex, element.Count, GL_FLOAT,
				GL_FALSE, layout.Stride(), (const void*)element.Offset);

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

	const Ref<VertexBuffer>& OpenGLVertexArray::GetVertexBuffer() const
	{
		return vertexBuffer;
	}

	const Ref<IndexBuffer>& OpenGLVertexArray::GetIndexBuffer() const
	{
		return indexBuffer;
	}
}