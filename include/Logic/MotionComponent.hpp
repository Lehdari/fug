#ifndef FUG_MOTION_COMPONENT_HPP
#define FUG_MOTION_COMPONENT_HPP

#include "Core/MathTypes.hpp"

namespace fug {

    class MotionComponent {

    public:
        MotionComponent(Vector3Glf const& = {0.f, 0.f, 0.f},
                        Vector3Glf const& = {0.f, 0.f, 0.f},
                        QuaternionGlf const& = {1.f, 0.f, 0.f, 0.f},
                        QuaternionGlf const& = {1.f, 0.f, 0.f, 0.f}); 

        Vector3Glf vel;
        Vector3Glf acc;
        QuaternionGlf angvel;
        QuaternionGlf angacc;

    }; 

} // namespace fug


#endif // FUG_MOTION_COMPONENT_HPP

