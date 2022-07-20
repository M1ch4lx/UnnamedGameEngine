#pragma once

#include "Shader.h"

namespace UEngine
{
	struct MaterialFlags
	{
		bool EnableDepthTest;

		MaterialFlags() :
			EnableDepthTest(false)
		{}
	};

	class Material :public FactoryObject
	{
		friend class MaterialLibrary;
	public:
		MaterialFlags Flags;

	private:
		Ref<Shader> shader;

		std::string name;

		std::vector<Ref<Uniform>> uniforms;

		std::unordered_map<std::string, unsigned int> indices;

		unsigned int shaderDataSize;

	public:
		const Ref<Shader>& GetShader() const;

		const std::string& GetName() const;

		const std::vector<Ref<Uniform>>& GetUniforms() const;

		unsigned int ShaderDataSize() const;

		unsigned int GetUniformIndex(const std::string& name);

		const Ref<Uniform>& GetUniform(unsigned int index);

		const Ref<Uniform>& GetUniform(const std::string& name);

	private:
		Material(const std::string& name, const Ref<Shader>& shader);
	};

	class MaterialInstance :public FactoryObject
	{
	private:
		Ref<Material> materialInstance;

		// Cache for all uniforms data
		std::vector<char> shaderData;

		// Contains pointer to buffered data of coresponding
		// uniform indicated by the same array index 
		std::vector<char*> uniformsData;

	public:
		MaterialInstance(const Ref<Material>& materialInstance);

		const Ref<Material>& GetMaterial() const;

		void Set(const std::string& name, const int val);

		void Set(const std::string& name, const float val);

		void Set(const std::string& name, const Vector2& val);

		void Set(const std::string& name, const Vector3& val);

		void Set(const std::string& name, const Vector4& val);

		void Set(const std::string& name, const Color4& val);

		void Set(const std::string& name, const Color3& val);

		void Set(const std::string& name, const Matrix4& matrix);

		void UploadData();

	private:
		template<typename T>
		void CacheUniformData(unsigned int index, const T& data)
		{
			*reinterpret_cast<T*>(uniformsData[index]) = data;
		}

		void VerifyUniformDataType(unsigned int index, ShaderDataType dataType);
	};

	class MaterialLibrary :public IService
	{
		SERVICE(MaterialLibrary)
	private:
		std::unordered_map<std::string, Ref<Material>> materials;

	public:
		const Ref<Material>& CreateMaterial(const std::string& name, const Ref<Shader>& shader);

		const Ref<Material>& FindMaterial(const std::string& name);

		const std::unordered_map<std::string, Ref<Material>>& Materials() const;

		Ref<MaterialInstance> CreateMaterialInstance(const std::string& matName);
	};
}