#include <Graphics/LightShaderBinding.hpp>

using namespace fug;

LightShaderBinding::LightShaderBinding(void) {}

const ResourcePointer<ShaderProgram>& LightShaderBinding::getShaderProgPtr() const
{
    return _shader;
}

const std::vector<GLint>& LightShaderBinding::getSamplerLocations() const
{
    return _samplerLocations;
}

const std::vector<GLint>& LightShaderBinding::getParameterLocations() const
{
    return _parameterLocations;
}
