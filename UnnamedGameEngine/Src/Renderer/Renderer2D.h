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
	public:
		virtual void BeginFrame() = 0;

		virtual void EndFrame() = 0;

		virtual void ClearScreen() = 0;

		virtual void ClearDepth() = 0;

		virtual void Render(const Ref<VertexArray>& vao) = 0;

		virtual void SetCamera(const Camera2D& camera) = 0;

		virtual const Camera2D& GetCamera() const = 0;

		virtual RenderContext* GetContext() const = 0;
	};
}