#pragma once

#include "OpenGLCommon.h"

#include "Renderer/Renderer2D.h"

namespace UEngine
{
	class OpenGLRenderer2D :public Renderer2D
	{
	public:
		OpenGLRenderer2D(RenderContext* context);

		virtual void BeginFrame() override;

		virtual void EndFrame() override;

		virtual void Clear() override;

		void Render(const Ref<VertexArray>& vao) override;
	};
}