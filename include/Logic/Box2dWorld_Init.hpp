#ifndef FUG_BOX2D_WORLD_INIT_HPP
#define FUG_BOX2D_WORLD_INIT_HPP


#include "Logic/Box2dWorld.hpp"
#include "Logic/Box2dBodyComponent.hpp"


namespace fug {

    class Box2dWorld_Init_Default {
    public:
        Box2dWorld_Init_Default(b2Vec2 gravity = b2Vec2(0, 0)) : gravity(gravity) {}

        b2Vec2 gravity;
    };

    #include "Box2dWorld_Init.tcc"

}


#endif // FUG_BOX2D_WORLD_INIT_HPP
