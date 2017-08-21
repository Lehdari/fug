
#include "Graphics/CameraComponent.hpp"

using namespace fug;

CameraComponent::CameraComponent(float const& fov,
                                 float const& aspect_ratio,
                                 float const& near,
                                 float const& far) :
    fov(fov), aspect_ratio(aspect_ratio), near(near), far(far)
{
    orientation.diagonal() << 1.f, 1.f, 1.f, 1.f;
    projection.diagonal() << 1.f, 1.f, 1.f, 1.f;
}

