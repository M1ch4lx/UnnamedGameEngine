#pragma once

#include "OpenGLCommon.h"

#include "Renderer/VertexArray.h"

namespace UEngine
{
	class OpenGLVertexArray :public VertexArray
	{
	private:
		unsigned int id;

		Ref<VertexBuffer> vertexBuffer;

		Ref<IndexBuffer> indexBuffer;

		void SetVertexBuffer(const Ref<VertexBuffer>& vertexBuffer);

		void SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer);

	public:
		OpenGLVertexArray(const Ref<VertexBuffer>& vertexBuffer, const Ref<IndexBuffer>& indexBuffer);

		~OpenGLVertexArray();

		void Bind() override;
	};
}