#include "Pch.h"
#include "Material.h"

namespace UEngine
{
    Material::Material(const std::string& name, const Ref<Shader>& shader) :
        name(name), shader(shader), shaderDataSize(0)
    {
        uniforms.reserve(8);
        unsigned int index = 0;
        for (const auto& uniform : shader->GetUniforms())
        {
            const auto prefix = uniform->Prefix();
            if (prefix == Uniform::MaterialPrefix())
            {
                uniforms.push_back(uniform);

                indices[uniform->GetName()] = index;
                index++;

                shaderDataSize += ShaderDataTypeSize(uniform->Type());
            }
        }
        uniforms.shrink_to_fit();
    }

    const Ref<Shader>& Material::GetShader() const
    {
        return shader;
    }

    const std::string& Material::GetName() const
    {
        return name;
    }

    const std::vector<Ref<Uniform>>& Material::GetUniforms() const
    {
        return uniforms;
    }

    unsigned int Material::ShaderDataSize() const
    {
        return shaderDataSize;
    }

    unsigned int Material::GetUniformIndex(const std::string& name)
    {
        const auto& iter = indices.find(name);
        if (iter == indices.end())
        {
            throw std::exception("Cannot find uniform index");
        }
        return iter->second;
    }

    const Ref<Uniform>& Material::GetUniform(unsigned int index)
    {
        return uniforms[index];
    }

    const Ref<Uniform>& Material::GetUniform(const std::string& name)
    {
        return uniforms[indices[name]];
    }

    MaterialInstance::MaterialInstance(const Ref<Material>& materialInstance) :
        materialInstance(materialInstance)
    {
        uniformsData.reserve(materialInstance->GetUniforms().size());

        shaderData.resize(materialInstance->ShaderDataSize());

        unsigned int offset = 0;
        for (const auto& uniform : materialInstance->GetUniforms())
        {
            uniformsData.emplace_back(shaderData.data() + offset);
            offset += ShaderDataTypeSize(uniform->Type());
        }
    }

    const Ref<Material>& MaterialInstance::GetMaterial() const
    {
        return materialInstance;
    }

    void MaterialInstance::Set(const std::string& name, const int val)
    {
        auto index = materialInstance->GetUniformIndex(name);
        VerifyUniformDataType(index, ShaderDataType::Int);
        CacheUniformData(index, val);
    }

    void MaterialInstance::Set(const std::string& name, const float val)
    {
        auto index = materialInstance->GetUniformIndex(name);
        VerifyUniformDataType(index, ShaderDataType::Float);
        CacheUniformData(index, val);
    }

    void MaterialInstance::Set(const std::string& name, const Vector2& val)
    {
        auto index = materialInstance->GetUniformIndex(name);
        VerifyUniformDataType(index, ShaderDataType::Float2);
        CacheUniformData(index, val);
    }

    void MaterialInstance::Set(const std::string& name, const Vector3& val)
    {
        auto index = materialInstance->GetUniformIndex(name);
        VerifyUniformDataType(index, ShaderDataType::Float3);
        CacheUniformData(index, val);
    }

    void MaterialInstance::Set(const std::string& name, const Vector4& val)
    {
        auto index = materialInstance->GetUniformIndex(name);
        VerifyUniformDataType(index, ShaderDataType::Float4);
        CacheUniformData(index, val);
    }

    void MaterialInstance::Set(const std::string& name, const Color4& val)
    {
        auto index = materialInstance->GetUniformIndex(name);
        VerifyUniformDataType(index, ShaderDataType::Float4);
        CacheUniformData(index, val);
    }

    void MaterialInstance::Set(const std::string& name, const Color3& val)
    {
        auto index = materialInstance->GetUniformIndex(name);
        VerifyUniformDataType(index, ShaderDataType::Float3);
        CacheUniformData(index, val);
    }

    void MaterialInstance::Set(const std::string& name, const Matrix4& matrix)
    {
        auto index = materialInstance->GetUniformIndex(name);
        VerifyUniformDataType(index, ShaderDataType::Mat4);
        CacheUniformData(index, matrix);
    }

    void MaterialInstance::UploadData()
    {
        for (unsigned int i = 0; i < uniformsData.size(); i++)
        {
            materialInstance->GetUniform(i)->Upload(uniformsData[i]);
        }
    }

    void MaterialInstance::VerifyUniformDataType(unsigned int index, ShaderDataType dataType)
    {
        if (materialInstance->GetUniform(index)->Type() != dataType)
        {
            throw std::exception("Provided wrong shader data type for uniform");
        }
    }

    const Ref<Material>& MaterialLibrary::CreateMaterial(const std::string& name, const Ref<Shader>& shader)
    {
        auto& materialInstance = materials[name];
        materialInstance = Ref<Material>(new Material(name, shader));
        return materialInstance;
    }

    const Ref<Material>& MaterialLibrary::FindMaterial(const std::string& name)
    {
        const auto& iter = materials.find(name);
        if (iter == materials.end())
        {
            throw std::exception("Cannot find material");
        }
        return iter->second;
    }

    const std::unordered_map<std::string, Ref<Material>>& MaterialLibrary::Materials() const
    {
        return materials;
    }

    Ref<MaterialInstance> MaterialLibrary::CreateMaterialInstance(const std::string& matName)
    {
        return Ref<MaterialInstance>(new MaterialInstance(FindMaterial(matName)));
    }
}