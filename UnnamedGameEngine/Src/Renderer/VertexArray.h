#pragma once

#include "Core/Common.h"

#include "VertexBuffer.h"

namespace UEngine
{
	class VertexArray :public GraphicsObject
	{
	public:
		virtual void SetVertexBuffer(const Ref<VertexBuffer>& vertexBuffer) = 0;

		virtual void SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer) = 0;

		virtual void Bind() = 0;
	};
}