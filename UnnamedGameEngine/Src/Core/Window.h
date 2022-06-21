#pragma once

#include "Common.h"

#include "Renderer/RenderContext.h"

#include "Signal.h"

namespace Atron
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

	class WindowResizeSignal :public Signal
	{
	private:
		unsigned int width;
		unsigned int height;

	public:
		WindowResizeSignal(unsigned int width, unsigned int height) :
			width(width), height(height)
		{}

		unsigned int Width() const
		{
			return width;
		}

		unsigned int Height() const
		{
			return height;
		}
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

		virtual RenderContext* GetContext() = 0;
	};
}