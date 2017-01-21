#ifndef FUG_BOX2D_BODY_COMPONENT_HPP
#define FUG_BOX2D_BODY_COMPONENT_HPP


#include <Box2D/Box2D.h>
#include "Core/Component.hpp"


namespace fug {

    class Box2dBodyComponent : public Component {
    public:
        Box2dBodyComponent(b2Body* body);
        ~Box2dBodyComponent();

        static b2World* world;
        b2Body* body;
    };

}


#endif // FUG_BOX2D_BODY_COMPONENT_HPP
