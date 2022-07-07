#pragma once

namespace UEngine
{
	class GraphicsObject
	{
	public:
		GraphicsObject() = default;

		virtual ~GraphicsObject() = default;

		GraphicsObject(const GraphicsObject&) = delete;

		GraphicsObject(GraphicsObject&&) = delete;

		GraphicsObject& operator=(const GraphicsObject&) = delete;

		GraphicsObject& operator=(GraphicsObject&&) = delete;
	};
}