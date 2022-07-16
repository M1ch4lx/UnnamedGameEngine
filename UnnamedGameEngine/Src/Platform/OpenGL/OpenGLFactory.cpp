#include "Pch.h"
#include "OpenGLFactory.h"

namespace UEngine
{
	Ref<Renderer2D> OpenGLFactory::CreateRenderer2D(RenderContext* context)
	{
		return Ref<Renderer2D>(new OpenGLRenderer2D(context));
	}

	Ref<Window> OpenGLFactory::CreateWindow()
	{
		return Ref<Window>(new OpenGLWindow());
	}

	Ref<VertexBuffer> OpenGLFactory::CreateVertexBuffer()
	{
		return Ref<VertexBuffer>(new OpenGLVertexBuffer());
	}

	Ref<IndexBuffer> OpenGLFactory::CreateIndexBuffer(unsigned int* indices, unsigned int count)
	{
		return Ref<IndexBuffer>(new OpenGLIndexBuffer(indices, count));
	}

	Ref<VertexArray> OpenGLFactory::CreateVertexArray(const Ref<VertexBuffer>& vbo, const Ref<IndexBuffer>& ibo)
	{
		return Ref<VertexArray>(new OpenGLVertexArray(vbo, ibo));
	}

	Ref<Shader> OpenGLFactory::CreateShader(const ShaderSource& vertexSrc, const ShaderSource& fragmentSrc)
	{
		return Ref<Shader>(new OpenGLShader(vertexSrc, fragmentSrc));
	}

	Ref<Texture> OpenGLFactory::CreateTexture(const Image& data)
	{
		return Ref<Texture>(new OpenGLTexture(data));
	}
}