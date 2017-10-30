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
    meshPtr->getMaterialPointer()->useMaterial(transform.transform, _cam.getView(), _cam.getProj());
    glBindVertexArray(meshPtr->getVAO());
    glDrawElements(GL_TRIANGLES, meshPtr->getIndexCount(), GL_UNSIGNED_INT, (GLvoid*)0);
    glBindVertexArray(0);
    return true;
}
