#include <Graphics/Renderer.hpp>


using namespace fug;

Renderer::Renderer(const Vector3Glf& position, const Vector3Glf& forward, const Vector3Glf& up,
                   const float& fov, const float& aspectRatio,
                   const float& near, const float& far) :
    _cam(position, forward, up, fov, aspectRatio, near ,far)
{
    ;
}

bool Renderer::operator()(MeshComponent& component) {
    component.draw(_cam.getView(), _cam.getProj());
    return true;
}
