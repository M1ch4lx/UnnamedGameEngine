#include "Pch.h"
#include "OpenGLUniform.h"

namespace UEngine
{
	OpenGLUniform::OpenGLUniform(Shader* shader, int location,
		const std::string& name, unsigned int size, ShaderDataType type) :
		shader(shader), location(location), size(size), name(name), type(type)
	{

	}

	int OpenGLUniform::Location() const
	{
		return location;
	}

	const std::string& OpenGLUniform::GetName() const
	{
		return name;
	}

	unsigned int OpenGLUniform::Size() const
	{
		return size;
	}

	ShaderDataType OpenGLUniform::Type() const
	{
		return type;
	}

	void OpenGLUniform::Upload(int val)
	{
		glUniform1i(location, val);
	}

	void OpenGLUniform::Upload(float val)
	{
		glUniform1f(location, val);
	}

	void OpenGLUniform::Upload(const Vector2& val)
	{
		glUniform2f(location, val.x, val.y);
	}

	void OpenGLUniform::Upload(const Vector3& val)
	{
		glUniform3f(location, val.x, val.y, val.z);
	}

	void OpenGLUniform::Upload(const Vector4& val)
	{
		glUniform4f(location, val.x, val.y, val.z, val.w);
	}

	void OpenGLUniform::Upload(const Color4& val)
	{
		glUniform4f(location, val.r, val.g, val.b, val.a);
	}

	void OpenGLUniform::Upload(const Color3& val)
	{
		glUniform3f(location, val.r, val.g, val.b);
	}

	void OpenGLUniform::Upload(const Matrix4& matrix)
	{
		glUniformMatrix4fv(location, 1, GL_TRUE, matrix.ConstData());
	}

	void OpenGLUniform::Upload(const int* values, unsigned int count)
	{
		glUniform1iv(location, count, values);
	}

	Shader* OpenGLUniform::ShaderProgram()
	{
		return shader;
	}

	void OpenGLUniform::BindShader()
	{
		shader->Bind();
	}
}