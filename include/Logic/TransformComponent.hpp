#ifndef FUG_TRANSFORM_COMPONENT_HPP
#define FUG_TRANSFORM_COMPONENT_HPP


#include <Core/MathTypes.hpp>
#include "Core/Component.hpp"


namespace fug {

    class TransformComponent : public Component {
    public:
        TransformComponent() :
            transform()
        {}
        
        Matrix4f transform;
    };

}


#endif // FUG_TRANSFORM_COMPONENT_HPP