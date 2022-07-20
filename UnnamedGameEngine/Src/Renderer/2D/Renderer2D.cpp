#include "Pch.h"
#include "Renderer2D.h"

namespace UEngine
{
	const VertexLayout& VertexTexColor::Layout()
	{
		static const VertexLayout layout = {
			VertexElementType::Float3,
			VertexElementType::Float2,
			VertexElementType::Float4
		};
		return layout;
	}
}