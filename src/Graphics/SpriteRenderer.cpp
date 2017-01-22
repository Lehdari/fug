#include <Graphics/SpriteRenderer.hpp>


using namespace fug;

SpriteRenderer::SpriteRenderer(const Vector3Glf& position, const Vector3Glf& forward, const Vector3Glf& up,
                   const float& fov, const float& aspectRatio,
                   const float& near, const float& far) :
    _cam(position, forward, up, fov, aspectRatio, near ,far)
{
    ;
}

bool SpriteRenderer::operator()(SpriteMeshComponent& component) {
    component.draw(_cam.getWorldToClip(), 0, 0);
    return true;
}
