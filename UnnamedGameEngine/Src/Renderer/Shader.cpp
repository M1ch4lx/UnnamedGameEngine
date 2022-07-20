#include "Pch.h"
#include "Shader.h"

namespace UEngine
{
	ShaderSource::ShaderSource(const std::string& path)
	{
		LoadFromFile(path);
	}

	void ShaderSource::LoadFromFile(const std::string& path)
	{
		std::ifstream file(path);

		if (!file.good())
		{
			throw std::exception(std::string("Cannot load file: " + path).c_str());
		}

		std::stringstream buffer;
		buffer << file.rdbuf();
		
		source = buffer.str();
	}

	void ShaderSource::Clear()
	{
		source.clear();
		source.shrink_to_fit();
	}

	const std::string& ShaderSource::Source() const
	{
		return source;
	}

	void Shader::SetUniform(const std::string& name, const int val)
	{
		GetUniform(name)->Upload(val);
	}

	void Shader::SetUniform(const std::string& name, const float val)
	{
		GetUniform(name)->Upload(val);
	}

	void Shader::SetUniform(const std::string& name, const Vector2& val)
	{
		GetUniform(name)->Upload(val);
	}

	void Shader::SetUniform(const std::string& name, const Vector3& val)
	{
		GetUniform(name)->Upload(val);
	}

	void Shader::SetUniform(const std::string& name, const Vector4& val)
	{
		GetUniform(name)->Upload(val);
	}

	void Shader::SetUniform(const std::string& name, const Color4& val)
	{
		GetUniform(name)->Upload(val);
	}

	void Shader::SetUniform(const std::string& name, const Color3& val)
	{
		GetUniform(name)->Upload(val);
	}

	void Shader::SetUniform(const std::string& name, const Matrix4& matrix)
	{
		GetUniform(name)->Upload(matrix);
	}

	void ShaderLibrary::AddShader(const std::string& name, const Ref<Shader>& shader)
	{
		shaders[name] = shader;
	}

	const Ref<Shader>& ShaderLibrary::FindShader(const std::string& name)
	{
		const auto& iter = shaders.find(name);
		if (iter == shaders.end())
		{
			throw std::exception("Cannot find shader");
		}
		return iter->second;
	}
}