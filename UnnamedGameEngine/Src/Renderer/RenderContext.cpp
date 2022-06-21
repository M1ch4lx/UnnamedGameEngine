#include "Pch.h"
#include "RenderContext.h"

namespace Atron
{
	RenderContext* RenderContext::currentContext = nullptr;

	RenderContext* RenderContext::Current()
	{
		return currentContext;
	}
}