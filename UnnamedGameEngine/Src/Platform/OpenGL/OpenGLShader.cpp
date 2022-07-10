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
	}

	void OpenGLShader::DeleteShaderProgram()
	{
		if (program)
		{
			glDeleteProgram(program);
			program = 0;
		}
	}

	inline int OpenGLShader::GetUniformLocation(const std::string& name)
	{
		return glGetUniformLocation(program, name.c_str());
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
		glUseProgram(program);
	}

	void OpenGLShader::SetFloat(const std::string& name, const float val)
	{
		glUniform1f(GetUniformLocation(name), val);
	}

	void OpenGLShader::SetFloat2(const std::string& name, const Vector2& val)
	{
		glUniform2f(GetUniformLocation(name), val.x, val.y);
	}

	void OpenGLShader::SetFloat3(const std::string& name, const Vector3& val)
	{
		glUniform3f(GetUniformLocation(name), val.x, val.y, val.z);
	}

	void OpenGLShader::SetFloat4(const std::string& name, const Vector4& val)
	{
		glUniform4f(GetUniformLocation(name), val.x, val.y, val.z, val.w);
	}

	void OpenGLShader::SetMatrix4(const std::string& name, const Matrix4& matrix)
	{
		glUniformMatrix4fv(GetUniformLocation(name), 1, GL_TRUE, matrix.ConstData());
	}
}