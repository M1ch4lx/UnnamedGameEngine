#include "Pch.h"
#include "OpenGLRenderer2D.h"

namespace UEngine
{
	OpenGLRenderer2D::OpenGLRenderer2D(RenderContext* context) :
		context(context)
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

	void OpenGLRenderer2D::ClearScreen()
	{
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void OpenGLRenderer2D::ClearDepth()
	{
		glClear(GL_DEPTH_BUFFER_BIT);
	}

	void OpenGLRenderer2D::Render(const Ref<VertexArray>& vao)
	{
		vao->Bind();

		auto vbo = vao->GetVertexBuffer();
		if (!vbo)
		{
			return;
		}

		if (auto ibo = vao->GetIndexBuffer())
		{
			glDrawElements(GL_TRIANGLES, ibo->GetCount(), GL_UNSIGNED_INT, nullptr);
		}
		else
		{
			glDrawArrays(GL_TRIANGLES, 0, vbo->GetCount());
		}
	}

	void OpenGLRenderer2D::SetCamera(const Camera2D& camera)
	{
		this->camera = camera;
	}

	const Camera2D& OpenGLRenderer2D::GetCamera() const
	{
		return camera;
	}

	RenderContext* OpenGLRenderer2D::GetContext() const
	{
		return context;
	}
}