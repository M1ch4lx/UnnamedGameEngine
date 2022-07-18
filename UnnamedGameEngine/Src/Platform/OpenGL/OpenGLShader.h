#pragma once

#include "Renderer/Shader.h"

#include "OpenGLCommon.h"

#include "OpenGLUniform.h"

namespace UEngine
{
	class OpenGLShader :public Shader
	{
	private:
		unsigned int program;

		std::unordered_map<std::string, int> locations;

		std::vector<Ref<Uniform>> uniforms;

	public:
		OpenGLShader(const ShaderSource& vertexSrc, const ShaderSource& fragmentSrc);

		~OpenGLShader();

		void Bind() override;

		Ref<Uniform> GetUniform(const std::string& name) override;

		const std::vector<Ref<Uniform>>& GetUniforms() override;

		static ShaderDataType ToShaderDataType(GLenum glShaderDataType);

	private:
		unsigned int CompileShader(GLenum shaderType, const ShaderSource& shaderSrc);

		void AttachShader(unsigned int shader);

		void CreateShaderProgram(const ShaderSource& vertexSrc, const ShaderSource& fragmentSrc);

		void DeleteShaderProgram();

		int GetUniformLocation(const std::string& name);
	};
}