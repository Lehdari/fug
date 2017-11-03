#include "Graphics/Renderer.hpp"


using namespace fug;
using RMType = RenderingMatrixType;

Renderer::Renderer(const Vector3Glf& position, const Vector3Glf& forward, const Vector3Glf& up,
                   const float& fov, const float& aspectRatio,
                   const float& near, const float& far) :
    _cam(position, forward, up, fov, aspectRatio, near, far)
{
}


bool Renderer::operator()(ModelComponent& model, TransformComponent& transform) {
    auto meshPtr = model.mesh;
    auto materialPtr = model.material;
    auto shaderPtr = materialPtr->getShaderProgPtr();

    // Calculate matrices
    Matrix4Glf modelToCam = _cam.getView() * transform.transform;
    Matrix4Glf modelToClip = _cam.getProj() * modelToCam;
    Matrix4Glf normalToCam = modelToCam.transpose().inverse();

    glUseProgram(shaderPtr->getId());

    // Bind textures
    auto textures = materialPtr->getTextures();
    for (auto i = 0u; i < textures.size(); i++) {
        glActiveTexture(GL_TEXTURE0 + i);
        textures[i].second->bind(GL_TEXTURE_2D);
        glUniform1i(textures[i].first, i);
    }

    // Set uniforms
    auto matrixLocations = shaderPtr->getMatrixLocations();
    glUniformMatrix4fv(matrixLocations[static_cast<size_t>(RMType::ModelToClip)], 1,
                       GL_FALSE, modelToClip.data());
    glUniformMatrix4fv(matrixLocations[static_cast<size_t>(RMType::ModelToView)], 1,
                       GL_FALSE, modelToCam.data());
    glUniformMatrix4fv(matrixLocations[static_cast<size_t>(RMType::NormalToView)], 1,
                       GL_FALSE, normalToCam.data());

    for (auto& u : materialPtr->getVec3s())
        glUniform3fv(u.first, 1, u.second.data());
    for (auto& u : materialPtr->getFloats())
        glUniform1f(u.first, u.second);

    // Draw
    glBindVertexArray(meshPtr->getVAO());
    glDrawElements(GL_TRIANGLES, meshPtr->getIndexCount(), GL_UNSIGNED_INT, (GLvoid*)0);
    glBindVertexArray(0);

    return true;
}
