#ifndef FUG_GRAPHICS_CAMERA_COMPONENT_HPP
#define FUG_GRAPHICS_CAMERA_COMPONENT_HPP

#include "Core/MathTypes.hpp"

namespace fug {

    class CameraComponent {

    public:
        CameraComponent(float const& fov,
                        float const& aspect_ratio,
                        float const& near,
                        float const& far);

        float fov;
        float aspect_ratio;
        float near;
        float far;

        Matrix4Glf orientation;
        Matrix4Glf projection;
    };

} // namespace fug


#endif // FUG_GRAPHICS_CAMERA_COMPONENT_HPP
