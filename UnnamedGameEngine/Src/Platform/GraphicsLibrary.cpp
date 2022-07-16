#include "Pch.h"
#include "GraphicsLibrary.h"

namespace UEngine
{
	GraphicsApi GraphicsLibrary::api = GraphicsApi::None;

	GraphicsFactory* GraphicsFactory::instance = nullptr;

	void GraphicsLibrary::InitializeOpenGL()
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

		GraphicsFactory::instance = new OpenGLFactory();

		api = GraphicsApi::OpenGL;
	}

	void GraphicsLibrary::TerminateOpenGL()
	{
		if (api != GraphicsApi::OpenGL)
		{
			throw std::exception("OpenGL is not initialized");
		}

		delete GraphicsFactory::instance;
		GraphicsFactory::instance = nullptr;

		glfwTerminate();

		api = GraphicsApi::None;
	}

	void GraphicsLibrary::Initialize(GraphicsApi api)
	{
		Terminate();

		switch (api)
		{
		case GraphicsApi::OpenGL:
			InitializeOpenGL();
			break;
		}
	}

	void GraphicsLibrary::Terminate()
	{
		switch (api)
		{
		case GraphicsApi::OpenGL:
			TerminateOpenGL();
			break;
		}
	}

	void GraphicsLibrary::InitializeImGui(const Ref<Window>& window)
	{
		ImGui::CreateContext();
		
		ImGui_ImplOpenGL3_Init();
		ImGui_ImplGlfw_InitForOpenGL(
			reinterpret_cast<OpenGLWindow*>(window.get())->window, true);
	}

	void GraphicsLibrary::TerminateImGui()
	{
		switch (api)
		{
		case GraphicsApi::OpenGL:
			ImGui_ImplOpenGL3_Shutdown();
			ImGui_ImplGlfw_Shutdown();
			break;
		}
		ImGui::DestroyContext();
	}

	GraphicsFactory* GraphicsLibrary::Factory()
	{
		return GraphicsFactory::instance;
	}
}