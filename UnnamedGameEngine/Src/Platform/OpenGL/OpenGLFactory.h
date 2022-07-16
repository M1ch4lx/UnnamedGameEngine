#pragma once

#include "Renderer/GraphicsFactory.h"

#include "OpenGLVertexBuffer.h"
#include "OpenGLVertexArray.h"
#include "OpenGLShader.h"
#include "OpenGLWindow.h"
#include "OpenGLRenderer2D.h"
#include "OpenGLTexture.h"

namespace UEngine
{
	class OpenGLFactory :public GraphicsFactory
	{
	public:
		Ref<Renderer2D> CreateRenderer2D(RenderContext* context) override;

		Ref<Window> CreateWindow() override;

		Ref<VertexBuffer> CreateVertexBuffer() override;

		Ref<IndexBuffer> CreateIndexBuffer(unsigned int* indices, unsigned int count) override;

		Ref<VertexArray> CreateVertexArray(const Ref<VertexBuffer>& vbo, const Ref<IndexBuffer>& ibo) override;

		Ref<Shader> CreateShader(const ShaderSource& vertexSrc, const ShaderSource& fragmentSrc) override;

		Ref<Texture> CreateTexture(const Image& data) override;
	};
}