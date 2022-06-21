#pragma once

#include "RenderContext.h"
#include "Camera.h"

#include "Core/Common.h"

#include "Geometry/Transformation.h"

namespace Atron
{
	class Renderer2D :public Transformable
	{
	private:
		Camera* camera;

		RenderContext* currentFrameContext;

	public:
		virtual void OnFrameBegin() = 0;

		virtual void OnFrameEnd() = 0;

		virtual void Clear() = 0;

		Renderer2D();

		virtual ~Renderer2D() {};

		void BeginFrame(RenderContext* context);

		void EndFrame();

		void SetCamera(Camera* camera);

		void ClearCamera();

		Camera* GetCamera();

		RenderContext* CurrentContext();
	};
}