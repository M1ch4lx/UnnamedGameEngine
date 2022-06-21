#include "Pch.h"
#include "RenderContext.h"

namespace UEngine
{
	RenderContext* RenderContext::currentContext = nullptr;

	RenderContext* RenderContext::Current()
	{
		return currentContext;
	}
}