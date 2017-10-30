#include "SpriteMaterial.hpp"

using namespace fug;

SpriteMaterial::SpriteMaterial(void) {}

void SpriteMaterial::useMaterial(const Matrix4Glf& mvp,
                                 const GLint& frameRow, const GLint& frameColumn) const
{
    glUseProgram(_shader->getId());
    bindTextures();
    glUniformMatrix4fv(_uniformLocations_Mat4[0], 1, GL_FALSE, mvp.data());
    glUniform1f(_uniformLocations_Float[0], _spriteW);
    glUniform1f(_uniformLocations_Float[1], _spriteH);
    glUniform1i(_uniformLocations_Int[0], frameRow);
    glUniform1i(_uniformLocations_Int[1], frameColumn);
}

void SpriteMaterial::useMaterial(const Matrix4Glf& model, const Matrix4Glf& camera,
                                 const GLint& frameRow, const GLint& frameColumn) const
{
    Matrix4Glf mvp = camera * model;
    glUseProgram(_shader->getId());
    bindTextures();
    glUniformMatrix4fv(_uniformLocations_Mat4[0], 1, GL_FALSE, mvp.data());
    glUniform1f(_uniformLocations_Float[0], _spriteW);
    glUniform1f(_uniformLocations_Float[1], _spriteH);
    glUniform1i(_uniformLocations_Int[0], frameRow);
    glUniform1i(_uniformLocations_Int[1], frameColumn);
}

GLuint SpriteMaterial::getShaderId(void) const
{
    return _shader->getId();
}

void SpriteMaterial::bindTextures(void) const
{
    auto nValidBinds = std::min(_textures.size(), _uniformLocations_Sampler2D.size());
    for (auto i=0u; i<nValidBinds; ++i) {
        glActiveTexture(GL_TEXTURE0+i);
        _textures[i]->bind(GL_TEXTURE_2D);
        glUniform1i(_uniformLocations_Sampler2D[i], i);
    }
}
