#pragma once

#include "OpenGL/OpenGLFactory.h"

namespace UEngine
{
	enum class GraphicsApi
	{
		None, OpenGL
	};

	class Graphics
	{
	private:
		Graphics() {};
		
		static GraphicsApi api;

		static GraphicsFactory* graphicsFactory;

	public:
		static void InitializeOpenGL();

		static void TerminateOpenGL();

		static GraphicsFactory* Factory();
	};
}