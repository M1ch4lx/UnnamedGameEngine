#pragma once

#include "Renderer/Shader.h"

#include "OpenGLCommon.h"

namespace UEngine
{
	class OpenGLShader :public Shader
	{
	private:
		unsigned int program;

		unsigned int CompileShader(GLenum shaderType, const ShaderSource& shaderSrc);

		void AttachShader(unsigned int shader);

		void CreateShaderProgram(const ShaderSource& vertexSrc, const ShaderSource& fragmentSrc);

		void DeleteShaderProgram();

		int GetUniformLocation(const std::string& name);

	public:
		OpenGLShader(const ShaderSource& vertexSrc, const ShaderSource& fragmentSrc);

		~OpenGLShader();

		void Bind() override;

		void SetUniform(const std::string& name, const int val) override;

		void SetUniform(const std::string& name, const float val) override;

		void SetUniform(const std::string& name, const Vector2& val) override;

		void SetUniform(const std::string& name, const Vector3& val) override;

		void SetUniform(const std::string& name, const Vector4& val) override;

		void SetUniform(const std::string& name, const Color4& val) override;

		void SetUniform(const std::string& name, const Color3& val) override;

		void SetUniform(const std::string& name, const Matrix4& matrix) override;
	};
}