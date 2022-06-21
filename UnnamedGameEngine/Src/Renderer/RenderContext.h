#pragma once

namespace Atron
{
	class RenderContext
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