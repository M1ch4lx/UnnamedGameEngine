#include "Pch.h"
#include "RenderingAPI.h"

namespace UEngine
{
	void RenderingAPI::InitializeOpenGL()
	{
		if (!glfwInit())
		{
			// TODO: Add assert or custom exception
			throw std::exception("Cannot initialize GLFW");
		}

		SetFactoryImplementation<Window, OpenGLWindow>();
		SetFactoryImplementation<Renderer2D, OpenGLRenderer2D>();
		SetFactoryImplementation<VertexBuffer, OpenGLVertexBuffer>();
		SetFactoryImplementation<IndexBuffer, OpenGLIndexBuffer>();
		SetFactoryImplementation<VertexArray, OpenGLVertexArray>();
	}

	void RenderingAPI::TerminateOpenGL()
	{
		glfwTerminate();
	}
}