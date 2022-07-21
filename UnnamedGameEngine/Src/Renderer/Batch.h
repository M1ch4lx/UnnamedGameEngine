#pragma once

#include "VertexArray.h"
#include "Material.h"

namespace UEngine
{
	class Batch
	{
	public:
		virtual const Ref<VertexArray>& GetVertexArray() const = 0;

		virtual const Ref<Material>& GetMaterial() const = 0;
	};
}