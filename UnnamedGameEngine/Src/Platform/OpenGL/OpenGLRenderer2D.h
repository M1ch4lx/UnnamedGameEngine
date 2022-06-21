#pragma once

#include "Renderer/Renderer2D.h"

namespace Atron
{
	class OpenGLRenderer2D :public Renderer2D
	{
	public:
		void OnFrameBegin() override;

		void OnFrameEnd() override;

		void Clear() override;

	};
}