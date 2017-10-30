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
