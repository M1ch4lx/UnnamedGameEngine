#pragma once

#include "GraphicsObject.h"
#include "RenderContext.h"
#include "Camera2D.h"

#include "Core/Common.h"

#include "Geometry/Transformation.h"

namespace UEngine
{
	class Renderer2D :public Transformable, public GraphicsObject
	{
	private:
		Camera2D* camera;

		RenderContext* currentFrameContext;

	public:
		virtual void OnFrameBegin() = 0;

		virtual void OnFrameEnd() = 0;

		virtual void Clear() = 0;

		Renderer2D();

		void BeginFrame(RenderContext* context);

		void EndFrame();

		void SetCamera(Camera2D* camera);

		void ClearCamera();

		Camera2D* GetCamera();

		RenderContext* CurrentContext();
	};
}