#include "Pch.h"
#include "OpenGLRenderer2D.h"

namespace UEngine
{
	OpenGLRenderer2D::OpenGLRenderer2D(RenderContext* context) :
		Renderer2D(context)
	{
		
	}

	void OpenGLRenderer2D::BeginFrame()
	{
		// TODO: do smth
	}

	void OpenGLRenderer2D::EndFrame()
	{
		GetContext()->SwapBuffers();
	}

	void OpenGLRenderer2D::Clear()
	{
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void OpenGLRenderer2D::Render(const Ref<VertexArray>& vao)
	{
		
	}
}