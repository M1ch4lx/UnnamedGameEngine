#pragma once

#include "Core/FactoryObject.h"

#include "RenderContext.h"
#include "VertexArray.h"
#include "Shader.h"

#include "Core/Common.h"

#include "Geometry/2D/Transformation2D.h"

#include "2D/Camera2D.h"

#include "Material.h"

namespace UEngine
{
	class Renderer2D :public Transformable2D, public FactoryObject
	{
	public:
		virtual void BeginScene(const Camera2D& camera) = 0;

		virtual void EndScene() = 0;

		virtual void Display() = 0;

		virtual void ClearScreen() = 0;

		virtual void ClearDepth() = 0;

		virtual RenderContext* GetContext() const = 0;

		virtual void SetMaterial(const Ref<MaterialInstance>& materialInstance) = 0;

		virtual void Render(const Ref<VertexArray>& vao, const Transformation2D& transform) = 0;

		virtual void RenderRectangle(const Transformation2D& transform) = 0;
	};
}