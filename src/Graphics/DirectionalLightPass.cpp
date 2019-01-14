#include "Graphics/DirectionalLightPass.hpp"

#include "Graphics/LightParameter.hpp"

using namespace fug;

DirectionalLightPass::DirectionalLightPass(const ResourcePointer<Mesh>& quadMesh,
                                           const Matrix4Glf& normalToView,
                                           float fovX,
                                           const Vector2Glf& viewportSize) :
    _quadMesh(quadMesh),
    _normalToView(normalToView),
    _fovX(fovX),
    _viewportSize(viewportSize)
{}

void DirectionalLightPass::initPass() const
{
    // Contribution of a directional light gets added to the entire scene
    glDepthMask(GL_FALSE);
    glDisable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendEquation(GL_FUNC_ADD);
    glBlendFunc(GL_ONE, GL_ONE);
}

bool DirectionalLightPass::operator()(DirectionalLightComponent& light) {
    auto shaderId = light.shader->getShaderProgPtr()->getId();
    glUseProgram(shaderId);

    // Bind textures to samplers
    for (auto i = 0u; i < light.shader->getSamplerLocations().size(); i++)
        glUniform1i(light.shader->getSamplerLocations()[i], i);

    // TODO: Optimize location gets to init,
    //       -> define all "common" uniform locations in shader like the matrices?
    // Bind homogenous corner vectors
    glUniform1f(glGetUniformLocation(shaderId, "uHalfFovX"), _fovX * 0.5);
    glUniform2fv(glGetUniformLocation(shaderId, "uViewportSize"), 1, _viewportSize.data());

    // Bind light attributes
    Vector4Glf dir = _normalToView * Vector4Glf(light.direction[0], light.direction[1], light.direction[2], 0.f);
    glUniform3fv(light.shader->getParameterLocations()[static_cast<size_t>(LightParameter::Direction)], 1, dir.data());
    glUniform3fv(light.shader->getParameterLocations()[static_cast<size_t>(LightParameter::Intensity)], 1, light.intensity.data());
    glUniform3fv(light.shader->getParameterLocations()[static_cast<size_t>(LightParameter::AmbientIntensity)], 1,
                 light.ambientInt.data());

    glBindVertexArray(_quadMesh->getVAO());
    glDrawElements(GL_TRIANGLES, _quadMesh->getIndexCount(), GL_UNSIGNED_INT, (GLvoid*)0);
    glBindVertexArray(0);

    return true;
}
