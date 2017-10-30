#include "Graphics/Renderer.hpp"


using namespace fug;


Renderer::Renderer(const Vector3Glf& position, const Vector3Glf& forward, const Vector3Glf& up,
                   const float& fov, const float& aspectRatio,
                   const float& near, const float& far) :
    _cam(position, forward, up, fov, aspectRatio, near, far)
{
}


bool Renderer::operator()(MeshComponent& mesh, TransformComponent& transform) {
    auto meshPtr = mesh.getMeshPointer();
    auto materialPtr = meshPtr->getMaterialPointer();

    // Retrieve relevant gl-variables
    GLint shaderId = materialPtr->getShaderProgPtr()->getId();
    auto textures = materialPtr->getTexturePtrs();
    auto uniformLocationsSampler2D = materialPtr->getUniformLocsSampler2D();
    auto uniformLocationsMat4 = materialPtr->getUniformLocsMat4();
    auto uniformLocationsVec3 = materialPtr->getUniformLocsVec3();
    auto uniformLocationsFloat = materialPtr->getUniformLocsFloat();
    auto specularColor = materialPtr->getSpecularColor();
    auto specularExp = materialPtr->getSpecularExp();

    // Calculate matrices
    Matrix4Glf modelToCam = _cam.getView() * transform.transform;
    Matrix4Glf modelToClip = _cam.getProj() * modelToCam;
    Matrix4Glf normalToCam = modelToCam.transpose().inverse();

    glUseProgram(shaderId);

    // Bind textures
    auto nValidBinds = std::min(textures.size(), uniformLocationsSampler2D.size());
    for (auto i = 0u; i < nValidBinds; ++i) {
        glActiveTexture(GL_TEXTURE0 + i);
        textures[i]->bind(GL_TEXTURE_2D);
        glUniform1i(uniformLocationsSampler2D[i], i);
    }

    // Set uniforms
    glUniformMatrix4fv(uniformLocationsMat4[0], 1, GL_FALSE, modelToClip.data());
    glUniformMatrix4fv(uniformLocationsMat4[1], 1, GL_FALSE, modelToCam.data());
    glUniformMatrix4fv(uniformLocationsMat4[2], 1, GL_FALSE, normalToCam.data());
    glUniform3fv(uniformLocationsVec3[0], 1, specularColor.data());
    glUniform1f(uniformLocationsFloat[0], specularExp);

    // Draw
    glBindVertexArray(meshPtr->getVAO());
    glDrawElements(GL_TRIANGLES, meshPtr->getIndexCount(), GL_UNSIGNED_INT, (GLvoid*)0);
    glBindVertexArray(0);

    return true;
}
