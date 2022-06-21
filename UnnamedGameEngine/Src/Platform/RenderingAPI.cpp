#include "Pch.h"
#include "RenderingAPI.h"

namespace Atron
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
	}

	void RenderingAPI::TerminateOpenGL()
	{
		glfwTerminate();
	}
}