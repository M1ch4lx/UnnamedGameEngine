#pragma once

#include "Core/FactoryObject.h"

#include "RenderContext.h"
#include "OrthographicCamera.h"
#include "VertexArray.h"
#include "Shader.h"

#include "Core/Common.h"

#include "Geometry/Transformation.h"

namespace UEngine
{
	struct Renderer2DShaders
	{
		Ref<Shader> FlatColor;
	};

	class Renderer2D :public Transformable, public FactoryObject
	{
	public:
		virtual void BeginScene(const OrthographicCamera2D& camera) = 0;

		virtual void EndScene() = 0;

		virtual void Display() = 0;

		virtual void ClearScreen() = 0;

		virtual void ClearDepth() = 0;

		virtual RenderContext* GetContext() const = 0;

		virtual Renderer2DShaders& ShadersConfiguration() = 0;

		virtual void RenderRectangle(const Transformation& transform, const Color4& color) = 0;
	};
}