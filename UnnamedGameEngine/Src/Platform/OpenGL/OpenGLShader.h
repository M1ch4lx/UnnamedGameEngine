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

		void SetFloat(const std::string& name, const float val) override;

		void SetFloat2(const std::string& name, const Vector2& val) override;

		void SetFloat3(const std::string& name, const Vector3& val) override;

		void SetFloat4(const std::string& name, const Vector4& val) override;

		void SetMatrix4(const std::string& name, const Matrix4& matrix) override;
	};
}