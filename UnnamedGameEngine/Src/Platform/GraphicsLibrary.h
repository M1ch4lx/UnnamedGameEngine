#pragma once

#include "Core/Core.h"

#include "OpenGL/OpenGLFactory.h"

namespace UEngine
{
	enum class GraphicsApi
	{
		None, OpenGL
	};

	class GraphicsLibrary
	{
	private:
		GraphicsLibrary() {};
		
		static GraphicsApi api;

	public:
		static void InitializeOpenGL();

		static void TerminateOpenGL();

		static void Initialize(GraphicsApi api);

		static void Terminate();

		static void InitializeImGui(const Ref<Window>& window);

		static void TerminateImGui();

		static GraphicsFactory* Factory();
	};
}