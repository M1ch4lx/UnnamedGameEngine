#include "Pch.h"
#include "OpenGLShader.h"

namespace UEngine
{
	unsigned int OpenGLShader::CompileShader(GLenum shaderType, const ShaderSource& shaderSrc)
	{
		unsigned int shader = glCreateShader(shaderType);

		auto sourceStr = shaderSrc.Source().c_str();

		glShaderSource(shader, 1, &sourceStr, nullptr);

		glCompileShader(shader);

		return shader;
	}

	inline void OpenGLShader::AttachShader(unsigned int shader)
	{
		glAttachShader(program, shader);
	}

	void OpenGLShader::CreateShaderProgram(const ShaderSource& vertexSrc, const ShaderSource& fragmentSrc)
	{
		DeleteShaderProgram();

		program = glCreateProgram();

		unsigned int vertexShader = CompileShader(GL_VERTEX_SHADER, vertexSrc);
		unsigned int fragmentShader = CompileShader(GL_FRAGMENT_SHADER, fragmentSrc);

		AttachShader(vertexShader);
		AttachShader(fragmentShader);

		glLinkProgram(program);
		
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);

		// Load and cache uniforms

		int count = 0;
		glGetProgramiv(program, GL_ACTIVE_UNIFORMS, &count);
		if (count == 0)
		{
			return;
		}

		uniforms.resize(static_cast<size_t>(count));
		
		// Maximum uniform name size
		constexpr unsigned int nameBufferSize = 64;

		for (int i = 0; i < count; i++)
		{
			char nameBuffer[nameBufferSize];
			int nameLength = 0;
			GLenum type = 0;
			int size = 0;

			glGetActiveUniform(program, i, nameBufferSize,
				&nameLength, &size, &type, nameBuffer);

			std::string name(nameBuffer, nameLength);

			int location = glGetUniformLocation(program, name.c_str());

			uniforms[location] = Ref<Uniform>(new OpenGLUniform(this,
				location, name, size, ToShaderDataType(type)));

			locations[name] = location;
		}
	}

	void OpenGLShader::DeleteShaderProgram()
	{
		if (program)
		{
			glDeleteProgram(program);
			program = 0;
		}
	}

	int OpenGLShader::GetUniformLocation(const std::string& name)
	{
		auto iter = locations.find(name);

		if (iter == locations.end())
		{
			throw std::exception("Cannot find uniform");
		}

		return iter->second;
	}

	OpenGLShader::OpenGLShader(const ShaderSource& vertexSrc, const ShaderSource& fragmentSrc) :
		program(0)
	{
		CreateShaderProgram(vertexSrc, fragmentSrc);
	}

	OpenGLShader::~OpenGLShader()
	{
		DeleteShaderProgram();
	}

	void OpenGLShader::Bind()
	{
		REMEMBER_BINDING();

		glUseProgram(program);
	}

	Ref<Uniform> OpenGLShader::GetUniform(const std::string& name)
	{
		return uniforms[GetUniformLocation(name)];
	}

	const std::vector<Ref<Uniform>>& OpenGLShader::GetUniforms()
	{
		return uniforms;
	}

	ShaderDataType OpenGLShader::ToShaderDataType(GLenum glShaderDataType)
	{
		switch (glShaderDataType)
		{
		case GL_FLOAT: return ShaderDataType::Float;
		case GL_FLOAT_VEC2: return ShaderDataType::Float2;
		case GL_FLOAT_VEC3: return ShaderDataType::Float3;
		case GL_FLOAT_VEC4: return ShaderDataType::Float4;

		case GL_INT: return ShaderDataType::Int;
		case GL_INT_VEC2: return ShaderDataType::Int2;
		case GL_INT_VEC3: return ShaderDataType::Int3;
		case GL_INT_VEC4: return ShaderDataType::Int4;

		case GL_FLOAT_MAT2: return ShaderDataType::Mat2;
		case GL_FLOAT_MAT3: return ShaderDataType::Mat3;
		case GL_FLOAT_MAT4: return ShaderDataType::Mat4;

		case GL_SAMPLER_2D: return ShaderDataType::Int;
		}

		return ShaderDataType::None;
	}
}