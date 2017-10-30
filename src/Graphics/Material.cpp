#include <Graphics/Material.hpp>

using namespace fug;

Material::Material(void) {}

const ResourcePointer<ShaderProgram>& Material::getShaderProgPtr() const
{
    return _shader;
}

const std::vector<ResourcePointer<Texture>>& Material::getTexturePtrs() const
{
    return _textures;
}

const Vector3Glf& Material::getSpecularColor() const
{
    return _specularColor;
}

float Material::getSpecularExp() const
{
    return _specularExp;
}

const std::vector<GLint>& Material::getUniformLocsSampler2D() const
{
    return _uniformLocations_Sampler2D;
}

const std::vector<GLint>& Material::getUniformLocsMat4() const
{
    return _uniformLocations_Mat4;
}

const std::vector<GLint>& Material::getUniformLocsVec3() const
{
    return _uniformLocations_Vec3;
}

const std::vector<GLint>& Material::getUniformLocsFloat() const
{
    return _uniformLocations_Float;
}
