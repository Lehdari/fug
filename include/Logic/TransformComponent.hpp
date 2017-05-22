#ifndef FUG_TRANSFORM_COMPONENT_HPP
#define FUG_TRANSFORM_COMPONENT_HPP

#include "Core/MathTypes.hpp"

namespace fug {

    class TransformComponent {

    public:
        TransformComponent(Vector3Glf const& = {0.f, 0.f, 0.f},
                           QuaternionGlf const& = {1.f, 0.f, 0.f, 0.f},
                           Vector3Glf const& = {1.f, 1.f, 1.f});

        Vector3Glf position;
        QuaternionGlf orientation;
        Vector3Glf scale;

        Matrix4f transform;
    };

} // namespace fug


#endif // FUG_TRANSFORM_COMPONENT_HPP
