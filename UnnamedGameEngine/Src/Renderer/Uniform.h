#pragma once

#include "Core/Core.h"

#include "Math/Math.h"

namespace UEngine
{
	enum class ShaderDataType
	{
		None,
		Float, Float2, Float3, Float4,
		Int, Int2, Int3, Int4,
		Mat2, Mat3, Mat4
	};

	unsigned int ShaderDataTypeSize(ShaderDataType type);

	class Shader;

	class Uniform :public FactoryObject
	{
	public:
		virtual int Location() const = 0;

		virtual const std::string& GetName() const = 0;

		virtual unsigned int Size() const = 0;

		virtual ShaderDataType Type() const = 0;

		virtual void Upload(const int val) = 0;
			 
		virtual void Upload(const float val) = 0;
			
		virtual void Upload(const Vector2& val) = 0;
			 
		virtual void Upload(const Vector3& val) = 0;
			 
		virtual void Upload(const Vector4& val) = 0;
			 
		virtual void Upload(const Color4& val) = 0;
			
		virtual void Upload(const Color3& val) = 0;
			 
		virtual void Upload(const Matrix4& matrix) = 0;

		virtual void Upload(const int* values, unsigned int count) = 0;

		virtual Shader* ShaderProgram() = 0;

		virtual void BindShader() = 0;

		void Upload(const void* data);

		std::string Prefix() const;
	
		static std::string ObtainPrefix(const std::string& uniformName);

		static constexpr const char* MaterialPrefix()
		{
			return "m_";
		}
	};
}