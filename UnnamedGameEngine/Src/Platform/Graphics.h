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

	public:
		static void InitializeOpenGL();

		static void TerminateOpenGL();

		static void InitializeImGui(const Ref<Window>& window);

		static void TerminateImGui();

		static GraphicsFactory* Factory();
	};
}