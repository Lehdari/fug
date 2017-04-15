#include "Graphics/DirectionalLightComponent.hpp"

using namespace fug;

DirectionalLightComponent::DirectionalLightComponent(ResourcePointer<ShaderProgram> shader,
                                                     const std::vector<std::string>& samplerNames,
                                                     const std::string& directionUniform, const Vector3Glf& direction,
                                                     const std::string& colorUniform, const Vector3Glf&color,
                                                     const std::string& directIntUniform, float directInt,
                                                     const std::string& ambientIntUniform, float ambientInt) :
    _shader(shader),
    _direction(direction),
    _color(color),
    _directInt(directInt),
    _ambientInt(ambientInt)
{
    for (auto& s : samplerNames)
        _samplerLocs.emplace_back(glGetUniformLocation(_shader->getId(),
                                                        s.c_str()));

    _directionULoc = glGetUniformLocation(_shader->getId(), directionUniform.c_str());
    _colorULoc = glGetUniformLocation(_shader->getId(), colorUniform.c_str());
    _directIntULoc = glGetUniformLocation(_shader->getId(), directIntUniform.c_str());
    _ambientIntULoc = glGetUniformLocation(_shader->getId(), ambientIntUniform.c_str());
}

void DirectionalLightComponent::bind(const Matrix4Glf& view)
{
    glUseProgram(_shader->getId());
    // Set samplers to textures
    for (auto i = 0u; i < _samplerLocs.size(); i++)
        glUniform1i(_samplerLocs[i], i);

    Vector4Glf dir = view.transpose().inverse() * Vector4Glf(_direction[0],
                                                             _direction[1],
                                                             _direction[2],
                                                             0.f);
    glUniform3fv(_directionULoc, 1, dir.data());
    glUniform3fv(_colorULoc, 1, _color.data());
    glUniform1f(_directIntULoc, _directInt);
    glUniform1f(_ambientIntULoc, _ambientInt);
}
