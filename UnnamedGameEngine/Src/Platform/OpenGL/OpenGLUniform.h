#pragma once

#include "Renderer/Uniform.h"
#include "Renderer/Shader.h"

#include "OpenGLCommon.h"

namespace UEngine
{
	class OpenGLUniform :public Uniform
	{
	private:
		Shader* shader;

		int location;

		std::string name;

		unsigned int size;

		ShaderDataType type;

	public:
		OpenGLUniform(Shader* shader, int location,
			const std::string& name, unsigned int size, ShaderDataType type);

		int Location() const override;

		const std::string& GetName() const override;

		unsigned int Size() const override;

		ShaderDataType Type() const override;

		void Upload(int val) override;

		void Upload(float val) override;

		void Upload(const Vector2& val) override;

		void Upload(const Vector3& val) override;

		void Upload(const Vector4& val) override;

		void Upload(const Color4& val) override;

		void Upload(const Color3& val) override;

		void Upload(const Matrix4& matrix) override;

		void Upload(const int* values, unsigned int count) override;

		Shader* ShaderProgram() override;

		void BindShader() override;
	};
}