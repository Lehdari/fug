#ifndef FUG_TRANSFORM_COMPONENT_HPP
#define FUG_TRANSFORM_COMPONENT_HPP


#include <Eigen/Geometry>
#include "Core/Component.hpp"


namespace fug {

    class TransformComponent : public Component {
    public:
        Eigen::Transform<float, 4, Affine> transform;
    };

}


#endif // FUG_TRANSFORM_COMPONENT_HPP
