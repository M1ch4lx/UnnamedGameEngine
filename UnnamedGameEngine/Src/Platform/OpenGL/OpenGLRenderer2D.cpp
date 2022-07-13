#include "Pch.h"
#include "OpenGLRenderer2D.h"

namespace UEngine
{
	void OpenGLRenderer2D::InitializeRectangleVao()
	{
		Vertex vertices[] = {
			{ 1.f * Unit(),  1.f * Unit(), 0.0f},   // top right
			{ 1.f * Unit(), -1.f * Unit(), 0.0f },   // bottom right
			{ -1.f * Unit(), -1.f * Unit(), 0.0f },  // bottom left
			{ -1.f * Unit(),  1.f * Unit(), 0.0f }   // top left 
		};

		unsigned int indices[] = {
			0, 1, 3,   // first triangle
			1, 2, 3    // second triangle
		};

		auto factory = GraphicsFactory::Get();
		
		const auto& layout = Vertex::Layout();

		auto vbo = factory->CreateVertexBuffer();
		vbo->SetData(vertices, 4, layout);

		auto ibo = factory->CreateIndexBuffer(indices, 6);

		rectangleVao = factory->CreateVertexArray(vbo, ibo);
	}

	OpenGLRenderer2D::OpenGLRenderer2D(RenderContext* context) :
		context(context)
	{
		InitializeRectangleVao();
	}

	void OpenGLRenderer2D::ClearScreen()
	{
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void OpenGLRenderer2D::ClearDepth()
	{
		glClear(GL_DEPTH_BUFFER_BIT);
	}

	RenderContext* OpenGLRenderer2D::GetContext() const
	{
		return context;
	}

	Renderer2DShaders& OpenGLRenderer2D::ShadersConfiguration()
	{
		return shaders;
	}

	void OpenGLRenderer2D::BeginScene(const OrthographicCamera2D& camera)
	{
		viewProjectionMatrix = camera.GetProjectionMatrix() * camera.GetViewMatrix();
	}

	void OpenGLRenderer2D::EndScene()
	{
		// Do smth
	}

	void OpenGLRenderer2D::Display()
	{
		context->SwapBuffers();
	}

	void OpenGLRenderer2D::RenderRectangle(const Transformation& transform, const Color4& color)
	{
		auto& shader = ShadersConfiguration().FlatColor;
		auto& vao = rectangleVao;

		shader->Bind();
		vao->Bind();

		shader->SetUniform("ViewProjection", viewProjectionMatrix);
		shader->SetUniform("Transform", transform.ToMatrix());
		shader->SetUniform("Color", color);

		glDrawElements(GL_TRIANGLES, vao->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
	}
}