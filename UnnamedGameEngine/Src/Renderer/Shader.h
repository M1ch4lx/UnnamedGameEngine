#pragma once

#include "Core/FactoryObject.h"

#include "Math/Vector.h"
#include "Math/Matrix.h"

#include "Uniform.h"

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

	class Shader :public FactoryObject
	{
	public:
		virtual void Bind() = 0;

		void SetUniform(const std::string& name, const int val);

		void SetUniform(const std::string& name, const float val);

		void SetUniform(const std::string& name, const Vector2& val);

		void SetUniform(const std::string& name, const Vector3& val);

		void SetUniform(const std::string& name, const Vector4& val);

		void SetUniform(const std::string& name, const Color4& val);

		void SetUniform(const std::string& name, const Color3& val);

		void SetUniform(const std::string& name, const Matrix4& matrix);

		virtual Ref<Uniform> GetUniform(const std::string& name) = 0;

		virtual const std::vector<Ref<Uniform>>& GetUniforms() = 0;
	};
}