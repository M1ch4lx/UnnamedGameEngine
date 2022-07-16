#pragma once

#include "OpenGLCommon.h"

#include "Renderer/RenderContext.h"

#include "Core/Window.h"

namespace UEngine
{
	class OpenGLContext :public RenderContext
	{
		friend class OpenGLWindow;
	private:
		GLFWwindow** window;

		WindowProps* properties;

		OpenGLContext(GLFWwindow** window, WindowProps* props);

	public:
		void Bind() override;

		void SwapBuffers() override;

		unsigned int Width() override;

		unsigned int Height() override;
	};

	class OpenGLWindow :public Window
	{
		friend class GraphicsLibrary;
	private:
		GLFWwindow* window;

		OpenGLContext context;

		WindowProps properties;

		static OpenGLWindow* ObtainWindowPtr(GLFWwindow* glfwWindow);

		static WindowProps& ObtainWindowProps(OpenGLWindow* window);

	public:
		OpenGLWindow();

		~OpenGLWindow();

		const WindowProps& Properties() override;

		void Open(const WindowProps& props) override;

		void Destroy() override;

		void ProcessEvents() override;

		bool IsOpen() override;

		RenderContext* Context() override;
	};
}