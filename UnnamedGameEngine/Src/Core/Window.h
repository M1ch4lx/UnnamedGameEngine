#pragma once

#include "Common.h"

#include "Renderer/RenderContext.h"

#include "Signal.h"

namespace UEngine
{
	struct WindowProps
	{
		std::string title;
		unsigned int width;
		unsigned int height;

		WindowProps() :
			width(0), height(0)
		{}

		WindowProps(const std::string& title, unsigned int width, unsigned int height) :
			title(title), width(width), height(height)
		{}
	};

	class WindowCloseSignal :public Signal
	{

	};

	class Window :public SignalListener
	{
	public:
		virtual void Open(const WindowProps& props) = 0;

		virtual void Destroy() = 0;

		virtual void ProcessEvents() = 0;

		virtual bool IsOpen() = 0;

		virtual const WindowProps& Properties() = 0;

		virtual RenderContext* Context() = 0;
	};
}