#include "Pch.h"
#include "Uniform.h"

namespace UEngine
{
	std::string Uniform::Prefix() const
	{
		return ObtainPrefix(GetName());
	}

	void Uniform::Upload(const void* data)
	{
		switch (Type())
		{
		case ShaderDataType::Float:
			Upload(*reinterpret_cast<const float*>(data));
			break;
		case ShaderDataType::Float2:
			Upload(*reinterpret_cast<const Vector2*>(data));
			break;
		case ShaderDataType::Float3:
			Upload(*reinterpret_cast<const Vector3*>(data));
			break;
		case ShaderDataType::Float4:
			Upload(*reinterpret_cast<const Vector4*>(data));
			break;
		case ShaderDataType::Int:
			Upload(*reinterpret_cast<const int*>(data));
			break;
		case ShaderDataType::Mat4:
			Upload(*reinterpret_cast<const Matrix4*>(data));
			break;
		}
	}

	std::string Uniform::ObtainPrefix(const std::string& uniformName)
	{
		constexpr unsigned int PrefixSize = 2;

		if (uniformName.size() <= PrefixSize ||
			uniformName[0] == '_' || uniformName[1] != '_')
		{
			return "";
		}

		return uniformName.substr(0, PrefixSize);
	}

	unsigned int ShaderDataTypeSize(ShaderDataType type)
	{
		constexpr unsigned int VarSize = sizeof(float);

		switch (type)
		{
		case ShaderDataType::Float: return VarSize;
		case ShaderDataType::Float2: return VarSize * 2;
		case ShaderDataType::Float3: return VarSize * 3;
		case ShaderDataType::Float4: return VarSize * 4;

		case ShaderDataType::Int: return VarSize;
		case ShaderDataType::Int2: return VarSize * 2;
		case ShaderDataType::Int3: return VarSize * 3;
		case ShaderDataType::Int4: return VarSize * 4;

		case ShaderDataType::Mat2: return VarSize * 2 * 2;
		case ShaderDataType::Mat3: return VarSize * 3 * 3;
		case ShaderDataType::Mat4: return VarSize * 4 * 4;
		}
		
		return 0;
	}
}