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
}