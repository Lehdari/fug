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
    auto shaderPtr = materialPtr->getShaderProgPtr();

    // Retrieve relevant gl-variables
    GLint shaderId = shaderPtr->getId();
    auto textures = materialPtr->getTexturePtrs();
    auto samplerLocations = shaderPtr->getSamplerLocations();
    auto uniformLocations = shaderPtr->getUniformLocations();
    auto specularColor = materialPtr->getSpecularColor();
    auto specularExp = materialPtr->getSpecularExp();

    // Calculate matrices
    Matrix4Glf modelToCam = _cam.getView() * transform.transform;
    Matrix4Glf modelToClip = _cam.getProj() * modelToCam;
    Matrix4Glf normalToCam = modelToCam.transpose().inverse();

    glUseProgram(shaderId);

    // Bind textures
    auto nValidBinds = std::min(textures.size(), samplerLocations.size());
    for (auto i = 0u; i < nValidBinds; ++i) {
        glActiveTexture(GL_TEXTURE0 + i);
        textures[i]->bind(GL_TEXTURE_2D);
        glUniform1i(samplerLocations[i], i);
    }

    // Set uniforms
    glUniformMatrix4fv(uniformLocations[0], 1, GL_FALSE, modelToClip.data());
    glUniformMatrix4fv(uniformLocations[1], 1, GL_FALSE, modelToCam.data());
    glUniformMatrix4fv(uniformLocations[2], 1, GL_FALSE, normalToCam.data());
    glUniform3fv(uniformLocations[3], 1, specularColor.data());
    glUniform1f(uniformLocations[4], specularExp);

    // Draw
    glBindVertexArray(meshPtr->getVAO());
    glDrawElements(GL_TRIANGLES, meshPtr->getIndexCount(), GL_UNSIGNED_INT, (GLvoid*)0);
    glBindVertexArray(0);

    return true;
}
