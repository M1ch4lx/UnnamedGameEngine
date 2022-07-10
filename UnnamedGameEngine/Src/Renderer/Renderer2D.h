#pragma once

#include "GraphicsObject.h"
#include "RenderContext.h"
#include "Camera2D.h"
#include "VertexArray.h"
#include "Shader.h"

#include "Core/Common.h"

#include "Geometry/Transformation.h"

namespace UEngine
{
	class Renderer2D :public Transformable, public GraphicsObject
	{
	private:
		RenderContext* context;

		Camera2D camera;

		// TODO: change this later to smth more organised
		// create rendering pipeline class or smth
		struct VP
		{
			Matrix4 view;
			Matrix4 projection;

		} transformations;

		void CreateViewProjectionMatrices();

	public:
		const Matrix4& GetViewMatrix() const;

		const Matrix4& GetProjectionMatrix() const;

	public:
		virtual void BeginFrame() = 0;

		virtual void EndFrame() = 0;

		virtual void Clear() = 0;

		virtual void Render(const Ref<VertexArray>& vao) = 0;

		Renderer2D(RenderContext* context);

		void SetCamera(const Camera2D& camera);

		const Camera2D& GetCamera() const;

		RenderContext* GetContext() const;
	};
}