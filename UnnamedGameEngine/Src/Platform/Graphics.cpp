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

	void Graphics::InitializeImGui(const Ref<Window>& window)
	{
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGui::StyleColorsDark();
		
		switch (api)
		{
		case GraphicsApi::OpenGL:
			ImGui_ImplGlfw_InitForOpenGL(reinterpret_cast<OpenGLWindow*>(window.get())->window, true);
			ImGui_ImplOpenGL3_Init("#version 410");
			break;

		default:
			TerminateImGui();
			throw std::exception("Graphics are not initialized");
			break;
		}
	}

	void Graphics::TerminateImGui()
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

	GraphicsFactory* Graphics::Factory()
	{
		return graphicsFactory;
	}
}