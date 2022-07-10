#pragma once

#include "Core/Window.h"

#include "VertexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Renderer2D.h"

namespace UEngine
{
	class GraphicsFactory
	{
	public:
		virtual Ref<Renderer2D> CreateRenderer2D(RenderContext* context) = 0;

		virtual Ref<Window> CreateWindow() = 0;

		virtual Ref<VertexBuffer> CreateVertexBuffer() = 0;

		virtual Ref<IndexBuffer> CreateIndexBuffer(unsigned int* indices, unsigned int count) = 0;

		virtual Ref<VertexArray> CreateVertexArray(const Ref<VertexBuffer>& vbo, const Ref<IndexBuffer>& ibo) = 0;

		virtual Ref<Shader> CreateShader(const ShaderSource& vertexSrc, const ShaderSource& fragmentSrc) = 0;
	};
}