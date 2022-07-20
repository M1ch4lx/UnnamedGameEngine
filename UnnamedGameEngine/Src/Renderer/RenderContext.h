#pragma once

#include "Core/FactoryObject.h"
#include "Core/Signal.h"

namespace UEngine
{
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

	class RenderContext :public FactoryObject, public SignalListener
	{
	protected:
		static RenderContext* currentContext;

	public:
		static RenderContext* Current();

		virtual void Bind() = 0;

		virtual void SwapBuffers() = 0;

		virtual unsigned int Width() = 0;

		virtual unsigned int Height() = 0;
	};
}