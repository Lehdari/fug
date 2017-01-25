#ifndef FUG_BOX2D_BODY_COMPONENT_HPP
#define FUG_BOX2D_BODY_COMPONENT_HPP


#include <Box2D/Box2D.h>


namespace fug {

    class Box2dBodyComponent {
    public:
        Box2dBodyComponent();
        Box2dBodyComponent(b2Body* body);
        Box2dBodyComponent(Box2dBodyComponent&& other);
        Box2dBodyComponent& operator=(Box2dBodyComponent&& other);
        ~Box2dBodyComponent();

        Box2dBodyComponent& operator=(const Box2dBodyComponent& other) = delete;
        Box2dBodyComponent(const Box2dBodyComponent& other) = delete;

        static b2World* world;
        b2Body* body;
    };

}


#endif // FUG_BOX2D_BODY_COMPONENT_HPP
