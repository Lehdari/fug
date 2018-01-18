#include "Graphics/PointLightPass.hpp"

#include "Graphics/LightParameter.hpp"

using namespace fug;
using RMType = RenderingMatrixType;

PointLightPass::PointLightPass(const Camera& c, std::shared_ptr<GBuffer> gb,
                               const std::vector<GLfloat>& hCorners, const Vector2Glf& viewportSize,
                               ResourcePointer<ShaderProgram>& stencilProg) :
    _cam(c),
    _hCorners(hCorners),
    _viewportSize(viewportSize),
    _gBuffer(gb),
    _stencilProg(stencilProg)
{}

bool PointLightPass::operator()(PointLightComponent& light, TransformComponent& t) {
    Matrix4Glf modelToView = _cam.getView() * t.transform;
    Matrix4Glf modelToClip = _cam.getProj() * modelToView;
    drawStencil(light, modelToClip);
    drawLight(light, modelToView, modelToClip);
    return true;
}

bool PointLightPass::drawStencil(PointLightComponent& light, Matrix4Glf& modelToClip) {
    // TODO: comments
    glUseProgram(_stencilProg->getId());

    _gBuffer->bindStencilPass();

    glEnable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);
    glClear(GL_STENCIL_BUFFER_BIT);

    glStencilFunc(GL_ALWAYS, 0, 0);
    glStencilOpSeparate(GL_BACK, GL_KEEP, GL_INCR_WRAP, GL_KEEP);
    glStencilOpSeparate(GL_FRONT, GL_KEEP, GL_DECR_WRAP, GL_KEEP);

    auto matrixLocations = _stencilProg->getMatrixLocations();
    glUniformMatrix4fv(matrixLocations[static_cast<size_t>(RMType::ModelToClip)], 1, GL_FALSE, modelToClip.data());

    glBindVertexArray(light.boundingMesh->getVAO());
    glDrawElements(GL_TRIANGLES, light.boundingMesh->getIndexCount(), GL_UNSIGNED_INT, (GLvoid*)0);
    glBindVertexArray(0);

    return true;
}

bool PointLightPass::drawLight(PointLightComponent& light, Matrix4Glf& modelToView, Matrix4Glf& modelToClip) {
    auto shaderId = light.shader->getShaderProgPtr()->getId();
    glUseProgram(shaderId);

    _gBuffer->bindLightPass();

    // TODO: explain these
    glDisable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendEquation(GL_FUNC_ADD);
    glBlendFunc(GL_ONE, GL_ONE);
    glEnable(GL_CULL_FACE);
    glStencilFunc(GL_NOTEQUAL, 0, 0xFF);
    glCullFace(GL_FRONT);

    // Bind textures to samplers
    for (auto i = 0u; i < light.shader->getSamplerLocations().size(); i++)
        glUniform1i(light.shader->getSamplerLocations()[i], i);

    // Bind bounding volume transformation
    auto matrixLocations = light.shader->getShaderProgPtr()->getMatrixLocations();
    glUniformMatrix4fv(matrixLocations[static_cast<size_t>(RMType::ModelToClip)], 1, GL_FALSE, modelToClip.data());

    // TODO: Optimize location gets to init,
    //       -> define all "common" uniform locations in shader like the matrices?
    // Bind homogenous corner vectors
    glUniform2fv(glGetUniformLocation(shaderId, "uCornerVecs"), 4, _hCorners.data());
    glUniform2fv(glGetUniformLocation(shaderId, "uViewportSize"), 1, _viewportSize.data());

    // Bind light attributes
    // TODO: pos to camspace
    Vector4Glf lightInCamspace = modelToView * Vector4Glf(0.f, 0.f, 0.f, 1.f);
    glUniform3fv(light.shader->getParameterLocations()[static_cast<size_t>(LightParameter::Position)], 1, lightInCamspace.data());
    glUniform3fv(light.shader->getParameterLocations()[static_cast<size_t>(LightParameter::Attenuation)], 1, light.attenuation.data());
    glUniform3fv(light.shader->getParameterLocations()[static_cast<size_t>(LightParameter::Intensity)], 1, light.intensity.data());

    // Draw bounding volume
    glBindVertexArray(light.boundingMesh->getVAO());
    glDrawElements(GL_TRIANGLES, light.boundingMesh->getIndexCount(), GL_UNSIGNED_INT, (GLvoid*)0);
    glBindVertexArray(0);

    // Disable blend and cull back faces
    glDisable(GL_BLEND);
    glCullFace(GL_BACK);

    return true;
}
