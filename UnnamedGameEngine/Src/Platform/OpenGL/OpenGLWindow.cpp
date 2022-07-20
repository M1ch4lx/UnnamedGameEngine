#include "Pch.h"
#include "OpenGLWindow.h"

namespace UEngine
{
	OpenGLWindow* OpenGLWindow::ObtainWindowPtr(GLFWwindow* glfwWindow)
	{
		return reinterpret_cast<OpenGLWindow*>(glfwGetWindowUserPointer(glfwWindow));
	}

	WindowProps& OpenGLWindow::ObtainWindowProps(OpenGLWindow* window)
	{
		return window->properties;
	}

	OpenGLWindow::OpenGLWindow() :
		window(nullptr), context(&window, &properties)
	{

	}

	OpenGLWindow::~OpenGLWindow()
	{
		Destroy();
	}

	const WindowProps& OpenGLWindow::Properties()
	{
		return properties;
	}

	void OpenGLWindow::Open(const WindowProps& props)
	{
		Destroy();

		window = glfwCreateWindow(props.width, props.height,
			props.title.c_str(), nullptr, nullptr);

		if (!window)
		{
			// TODO: Add assert or custom exception
			throw std::exception("Cannot create window");
		}

		properties = props;

		glfwSetWindowUserPointer(window, this);

		// Resize callback
		glfwSetFramebufferSizeCallback(window, [](GLFWwindow* wnd, int width, int height)
			{
				auto window = ObtainWindowPtr(wnd);

				auto& props = ObtainWindowProps(window);
				props.width = (unsigned int)width;
				props.height = (unsigned int)height;

				WindowResizeSignal signal(props.width, props.height);

				window->EmitSignal(signal);
				window->Context()->EmitSignal(signal);
			});

		// Close callback
		glfwSetWindowCloseCallback(window, [](GLFWwindow* wnd)
			{
				auto window = ObtainWindowPtr(wnd);

				// For now close flag will be always false
				glfwSetWindowShouldClose(wnd, false);

				WindowCloseSignal signal;

				window->EmitSignal(signal);
			});

		context.Bind();
		gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

		glDebugMessageCallback([](GLenum source, GLenum type, GLuint id,
			GLenum severity, GLsizei length, const GLchar* message, const void* userData)
			{
				std::cout << "[OpenGL Error] " << type << ": " << message << std::endl;

			}, nullptr);
	}

	void OpenGLWindow::Destroy()
	{
		if (window)
		{
			glfwDestroyWindow(window);
			window = nullptr;
		}
	}

	void OpenGLWindow::ProcessEvents()
	{
		glfwPollEvents();
	}

	bool OpenGLWindow::IsOpen()
	{
		return window;
	}

	RenderContext* OpenGLWindow::Context()
	{
		return reinterpret_cast<RenderContext*>(&context);
	}

	OpenGLContext::OpenGLContext(GLFWwindow** window, WindowProps* props) :
		window(window), properties(props)
	{

	}

	void OpenGLContext::Bind()
	{
		if (currentContext != this && *window)
		{
			glfwMakeContextCurrent(*window);

			currentContext = this;
		}
	}

	void OpenGLContext::SwapBuffers()
	{
		if (*window)
		{
			glfwSwapBuffers(*window);
		}
	}

	unsigned int OpenGLContext::Width()
	{
		return properties->width;
	}

	unsigned int OpenGLContext::Height()
	{
		return properties->height;
	}
}