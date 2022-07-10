#include "Pch.h"
#include "Renderer2D.h"

namespace UEngine
{
	void Renderer2D::CreateViewProjectionMatrices()
	{
		auto negPos = transformation.position * -1;
		transformations.view = TranslationMatrix(Vector3(negPos.x, negPos.y, 0.f));
		
		auto cameraSize = camera.CalculateSize();
		transformations.projection = ScaleMatrix(
			2.f / cameraSize.x, 2.f / cameraSize.y);
	}

	const Matrix4& Renderer2D::GetViewMatrix() const
	{
		return transformations.view;
	}

	const Matrix4& Renderer2D::GetProjectionMatrix() const
	{
		return transformations.projection;
	}

	Renderer2D::Renderer2D(RenderContext* context) :
		context(context)
	{
		CreateViewProjectionMatrices();
	}

	void Renderer2D::SetCamera(const Camera2D& camera)
	{
		this->camera = camera;
		CreateViewProjectionMatrices();
	}

	const Camera2D& Renderer2D::GetCamera() const
	{
		return camera;
	}

	RenderContext* Renderer2D::GetContext() const
	{
		return context;
	}
}