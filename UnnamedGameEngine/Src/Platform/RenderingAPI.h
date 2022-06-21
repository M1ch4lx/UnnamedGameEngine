#pragma once

#include "OpenGL/OpenGLRenderingAPI.h"

#include "Core/Factory.h"

namespace UEngine
{
	class RenderingAPI
	{
	private:
		RenderingAPI() {};

	public:
		static void InitializeOpenGL();

		static void TerminateOpenGL();
	};
}