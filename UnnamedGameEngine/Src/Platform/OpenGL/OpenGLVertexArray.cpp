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

		auto GLComponentType = [](VertexElementType type)
		{
			switch (type)
			{
			case VertexElementType::Float:
			case VertexElementType::Float2:
			case VertexElementType::Float3:
			case VertexElementType::Float4:
				return GL_FLOAT;

			case VertexElementType::Int:
				return GL_INT;
			}
			
			throw std::exception("Vertex element type not supported");
		};

		for (const auto& element : layout.Elements())
		{
			auto componentType = GLComponentType(element.Type);

			if (componentType == GL_FLOAT)
			{
				glVertexAttribPointer(attribIndex, element.Count, componentType,
					GL_FALSE, layout.Stride(), (const void*)element.Offset);
			}
			else // Integral type uses different function
			{
				glVertexAttribIPointer(attribIndex, element.Count, componentType,
					layout.Stride(), (const void*)element.Offset);
			}

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