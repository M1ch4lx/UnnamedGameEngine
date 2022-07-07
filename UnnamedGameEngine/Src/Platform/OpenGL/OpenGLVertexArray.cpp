#include "Pch.h"
#include "OpenGLVertexArray.h"

namespace UEngine
{
	OpenGLVertexArray::OpenGLVertexArray() :
		id(0)
	{
		glGenVertexArrays(1, &id);
	}

	OpenGLVertexArray::~OpenGLVertexArray()
	{
		glDeleteVertexArrays(1, &id);
	}

	void OpenGLVertexArray::SetVertexBuffer(const Ref<VertexBuffer>& buffer)
	{
		if (vertexBuffer)
		{
			return;
		}
		vertexBuffer = buffer;

		glBindVertexArray(id);

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
		if (indexBuffer)
		{
			return;
		}
		indexBuffer = buffer;

		glBindVertexArray(id);
	}

	void OpenGLVertexArray::Bind()
	{
		glBindVertexArray(id);
	}
}