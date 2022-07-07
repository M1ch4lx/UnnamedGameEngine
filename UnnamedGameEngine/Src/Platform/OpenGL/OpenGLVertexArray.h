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

	public:
		OpenGLVertexArray();

		~OpenGLVertexArray();

		void SetVertexBuffer(const Ref<VertexBuffer>& vertexBuffer) override;

		void SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer) override;

		void Bind() override;
	};
}