#pragma once

#include "GraphicsObject.h"

#include "Math/Vector.h"
#include "Math/Matrix.h"

#include <string>
#include <fstream>
#include <sstream>

namespace UEngine
{
	class ShaderSource
	{
	private:
		std::string source;

	public:
		ShaderSource() = default;

		ShaderSource(const std::string& path);

		void LoadFromFile(const std::string& path);

		void Clear();

		const std::string& Source() const;
	};

	class Shader :public GraphicsObject
	{
	public:
		virtual void Bind() = 0;

		virtual void SetFloat(const std::string& name, const float val) = 0;

		virtual void SetFloat2(const std::string& name, const Vector2& val) = 0;

		virtual void SetFloat3(const std::string& name, const Vector3& val) = 0;

		virtual void SetFloat4(const std::string& name, const Vector4& val) = 0;

		virtual void SetMatrix4(const std::string& name, const Matrix4& matrix) = 0;
	};
}