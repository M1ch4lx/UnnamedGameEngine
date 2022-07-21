#pragma once

#include "Math/Math.h"

#include "Geometry/Vertex.h"

namespace UEngine
{
	struct VertexTexColor
	{
		Vector3 Position;

		Vector2 TexCoord;

		Color4 Color;

		VertexTexColor() = default;

		VertexTexColor(const Vector3& Position, const Vector2& TexCoord, const Color4& Color) :
			Position(Position), TexCoord(TexCoord), Color(Color)
		{}

		static const VertexLayout& Layout();
	};
}