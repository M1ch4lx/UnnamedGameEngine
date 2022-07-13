#pragma once

#include "Core/Common.h"

#include "VertexBuffer.h"

namespace UEngine
{
	class VertexArray :public FactoryObject
	{
	public:
		virtual void Bind() = 0;

		virtual const Ref<VertexBuffer>& GetVertexBuffer() const = 0;

		virtual const Ref<IndexBuffer>& GetIndexBuffer() const = 0;
	};
}