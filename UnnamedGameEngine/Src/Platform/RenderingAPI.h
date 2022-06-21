#pragma once

#include "OpenGL/OpenGLRenderingAPI.h"

#include "Core/Factory.h"

namespace Atron
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