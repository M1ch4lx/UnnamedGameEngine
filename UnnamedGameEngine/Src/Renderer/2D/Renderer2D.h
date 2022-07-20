#pragma once

#include "Core/FactoryObject.h"

#include "Renderer/RenderContext.h"
#include "Renderer/VertexArray.h"
#include "Renderer/Shader.h"
#include "Renderer/Material.h"

#include "Core/Common.h"

#include "Geometry/2D/Transformation2D.h"

#include "Camera2D.h"

#include "Renderer/Blending.h"

namespace UEngine
{
	class Renderer2D :public FactoryObject
	{
	public:
		virtual void BeginScene(const Camera2D& camera) = 0;

		virtual void EndScene() = 0;

		virtual void Display() = 0;

		virtual void ClearScreen() = 0;

		virtual void SetClearColor(const Color3& color) = 0;

		virtual const Color3& GetClearColor() const = 0;

		virtual void ClearDepth() = 0;

		virtual RenderContext* GetContext() const = 0;

		virtual void SetMaterial(const Ref<MaterialInstance>& materialInstance) = 0;

		virtual void Render(const Ref<VertexArray>& vao, const Transformation2D& transform) = 0;

		virtual void RenderRectangle(const Transformation2D& transform) = 0;
	};

	struct VertexTexColor
	{
		Vector3 position;

		Vector2 texCoord;

		Color4 color;

		VertexTexColor() = default;

		VertexTexColor(const Vector3& position, const Vector2& texCoord, const Color4& color) :
			position(position), texCoord(texCoord), color(color)
		{}

		static const VertexLayout& Layout();
	};
}