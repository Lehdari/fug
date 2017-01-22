#include <Graphics/Material.hpp>

using namespace fug;

Material::Material(void) {}

void Material::useMaterial(const Matrix4Glf& model, const Matrix4Glf& camera,
                           const Matrix4Glf& proj) const
{
    Matrix4Glf modelToCam = camera * model;
    Matrix4Glf modelToClip = proj * modelToCam;
    Matrix4Glf normalToCam = modelToCam.transpose().inverse();
    glUseProgram(_shader->getId());
    bindTextures();
    glUniformMatrix4fv(_uniformLocations_Mat4[0], 1, GL_FALSE, modelToClip.data());
    glUniformMatrix4fv(_uniformLocations_Mat4[1], 1, GL_FALSE, modelToCam.data());
    glUniformMatrix4fv(_uniformLocations_Mat4[2], 1, GL_FALSE, normalToCam.data());
    glUniform3fv(_uniformLocations_Vec3[0], 1, _specularColor.data());
    glUniform1f(_uniformLocations_Float[0], _specularExp);
}

GLuint Material::getShaderId(void) const
{
    return _shader->getId();
}

void Material::bindTextures(void) const
{
    auto nValidBinds = std::min(_textures.size(), _uniformLocations_Sampler2D.size());
    for (auto i=0u; i<nValidBinds; ++i) {
        glActiveTexture(GL_TEXTURE0+i);
        _textures[i]->bind(GL_TEXTURE_2D);
        glUniform1i(_uniformLocations_Sampler2D[i], i);
    }
}
