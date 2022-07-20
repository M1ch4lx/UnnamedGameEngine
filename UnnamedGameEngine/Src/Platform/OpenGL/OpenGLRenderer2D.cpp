#include "Pch.h"
#include "OpenGLRenderer2D.h"

namespace UEngine
{
	OpenGLRenderer2D::OpenGLRenderer2D(RenderContext* context) :
		context(context)
	{
		clearColor = Color(0.f, 0.f, 0.f);
		SetClearColor(clearColor);
	}

	void OpenGLRenderer2D::ClearScreen()
	{
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void OpenGLRenderer2D::SetClearColor(const Color3& color)
	{
		clearColor = color;
		glClearColor(color.r, color.g, color.b, 1.f);
	}

	const Color3& OpenGLRenderer2D::GetClearColor() const
	{
		return clearColor;
	}

	void OpenGLRenderer2D::ClearDepth()
	{
		glClear(GL_DEPTH_BUFFER_BIT);
	}

	RenderContext* OpenGLRenderer2D::GetContext() const
	{
		return context;
	}

	void OpenGLRenderer2D::BeginScene(const Camera2D& camera)
	{
		viewProjectionMatrix = camera.GetProjectionMatrix() * camera.GetViewMatrix();
		const auto& vp = camera.GetViewport();

		const float width = static_cast<const float>(context->Width());
		const float height = static_cast<const float>(context->Height());
		
		DenormalizedViewport denormalizedVp(
			static_cast<int>(height * vp.Top),
			static_cast<int>(width * vp.Left),
			static_cast<int>(height * vp.Bottom),
			static_cast<int>(width * vp.Right));

		// Reduces redundant glViewport calling
		if (viewport != denormalizedVp)
		{
			viewport = denormalizedVp;

			glViewport(denormalizedVp.Left, denormalizedVp.Top,
				denormalizedVp.Right - denormalizedVp.Left,
				denormalizedVp.Bottom - denormalizedVp.Top);
		}
	}

	void OpenGLRenderer2D::EndScene()
	{
		// Do smth
	}

	void OpenGLRenderer2D::Display()
	{
		context->SwapBuffers();
	}

	void OpenGLRenderer2D::SetMaterial(const Ref<MaterialInstance>& materialInstance)
	{
		this->materialInstance = materialInstance;
	}

	void OpenGLRenderer2D::Render(const Ref<VertexArray>& vao, const Transformation2D& transform)
	{
		const auto& shader = materialInstance->GetMaterial()->GetShader();
		shader->Bind();
		vao->Bind();

		shader->SetUniform("ViewProjection", viewProjectionMatrix);
		shader->SetUniform("Transform", transform.ToMatrix());

		materialInstance->UploadData();

		glDrawElements(GL_TRIANGLES, vao->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
	}

	void OpenGLRenderer2D::RenderRectangle(const Transformation2D& transform)
	{
		static Ref<VertexArray> rectangleVao;
		if (!rectangleVao)
		{
			Vertex vertices[] = {
			{ 1.f,  1.f, 0.0f},   // top right
			{ 1.f, -1.f, 0.0f },   // bottom right
			{ -1.f, -1.f, 0.0f },  // bottom left
			{ -1.f,  1.f, 0.0f }   // top left 
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

		Render(rectangleVao, transform);
	}
}