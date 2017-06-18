#include "Graphics/PointLightComponent.hpp"

using namespace fug;

PointLightComponent::PointLightComponent(ResourcePointer<ShaderProgram> shader,
                                         const std::vector<std::string>& samplerNames,
                                         const std::string& positionUniform, const Vector3Glf& position,
                                         const std::string& colorUniform, const Vector3Glf& color,
                                         const std::string& directIntUniform, float directInt,
                                         const std::string& attenConstUniform, float attenConst,
                                         const std::string& attenLinUniform, float attenLin,
                                         const std::string& attenExpUniform, float attenExp) :
    _shader(shader),
    _position(position),
    _color(color),
    _directInt(directInt),
    _attenConst(attenConst),
    _attenLin(attenLin),
    _attenExp(attenExp)
{
    for (auto& s : samplerNames)
        _samplerLocs.emplace_back(glGetUniformLocation(_shader->getId(),
                                                        s.c_str()));

    _positionULoc = glGetUniformLocation(_shader->getId(), positionUniform.c_str());
    _colorULoc = glGetUniformLocation(_shader->getId(), colorUniform.c_str());
    _directIntULoc = glGetUniformLocation(_shader->getId(), directIntUniform.c_str());
    _attenConstULoc = glGetUniformLocation(_shader->getId(), attenConstUniform.c_str());
    _attenLinULoc = glGetUniformLocation(_shader->getId(), attenLinUniform.c_str());
    _attenExpULoc = glGetUniformLocation(_shader->getId(), attenExpUniform.c_str());
}

void PointLightComponent::bind(const Matrix4Glf& view)
{
    glUseProgram(_shader->getId());
    // Set samplers to textures
    for (auto i = 0u; i < _samplerLocs.size(); i++)
        glUniform1i(_samplerLocs[i], i);

    Vector4Glf pos = view * Vector4Glf(_position[0], _position[1], _position[2], 0.f);
    glUniform3fv(_positionULoc, 1, pos.data());
    glUniform3fv(_colorULoc, 1, _color.data());
    glUniform1f(_directIntULoc, _directInt);
    glUniform1f(_attenConstULoc, _attenConst);
    glUniform1f(_attenLinULoc, _attenLin);
    glUniform1f(_attenExpULoc, _attenExp);
}

GLuint PointLightComponent::getShaderId()
{
    return _shader->getId();
}
