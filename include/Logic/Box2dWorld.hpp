#ifndef FUG_BOX2D_WORLD_HPP
#define FUG_BOX2D_WORLD_HPP


#include "Core/Resource.hpp"
#include "Box2D/Box2D.h"


namespace fug {

    class FUG_RESOURCE(Box2dWorld) {
    public:
        Box2dWorld(void);
        ~Box2dWorld(void);

        Box2dWorld(const Box2dWorld&)               = delete;
        Box2dWorld& operator=(const Box2dWorld&)    = delete;
        Box2dWorld(Box2dWorld&&);
        Box2dWorld& operator=(Box2dWorld&&);

        FUG_RESOURCE_INIT_DESTROY_DECL

        b2World* world;
    };

}


#endif // FUG_BOX2D_WORLD_HPP
