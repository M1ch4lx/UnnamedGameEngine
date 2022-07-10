#include "Pch.h"
#include "Graphics.h"

namespace UEngine
{
	GraphicsApi Graphics::api = GraphicsApi::None;

	GraphicsFactory* Graphics::graphicsFactory = nullptr;

	void Graphics::InitializeOpenGL()
	{
		if (api != GraphicsApi::None)
		{
			throw std::exception("Graphics already initialized");
		}

		if (!glfwInit())
		{
			// TODO: Add assert or custom exception
			throw std::exception("Cannot initialize GLFW");
		}

		graphicsFactory = new OpenGLFactory();

		api = GraphicsApi::OpenGL;
	}

	void Graphics::TerminateOpenGL()
	{
		if (api != GraphicsApi::OpenGL)
		{
			throw std::exception("OpenGL is not initialized");
		}

		delete graphicsFactory;
		graphicsFactory = nullptr;

		glfwTerminate();

		api = GraphicsApi::None;
	}

	GraphicsFactory* Graphics::Factory()
	{
		return graphicsFactory;
	}
}