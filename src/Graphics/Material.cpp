#include <Graphics/Material.hpp>

using namespace fug;

Material::Material(void) {}

const ResourcePointer<ShaderProgram>& Material::getShaderProgPtr() const
{
    return _shader;
}

const std::vector<std::pair<GLint, ResourcePointer<Texture>>>& Material::getTextures() const
{
    return _textures;
}

const std::vector<std::pair<GLint, Vector3Glf>>& Material::getVec3s() const
{
    return _vec3s;
}

const std::vector<std::pair<GLint, float>>& Material::getFloats() const
{
    return _floats;
}
