#include "Pch.h"
#include "Renderer2D.h"

namespace Atron
{
	Renderer2D::Renderer2D() :
		camera(nullptr), currentFrameContext(nullptr)
	{}

	void Renderer2D::BeginFrame(RenderContext* context)
	{
		if (currentFrameContext)
		{
			throw std::exception("End current frame first");
		}
		currentFrameContext = context;

		context->Bind();

		OnFrameBegin();
	}

	void Renderer2D::EndFrame()
	{
		if (currentFrameContext)
		{
			OnFrameEnd();

			currentFrameContext = nullptr;
		}
	}

	void Renderer2D::SetCamera(Camera* camera)
	{
		this->camera = camera;
	}

	void Renderer2D::ClearCamera()
	{
		camera = nullptr;
	}

	Camera* Renderer2D::GetCamera()
	{
		return camera;
	}

	RenderContext* Renderer2D::CurrentContext()
	{
		return currentFrameContext;
	}
}