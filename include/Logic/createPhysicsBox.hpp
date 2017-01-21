#ifndef FUG_CREATE_PHYSICS_BOX_HPP
#define FUG_CREATE_PHYSICS_BOX_HPP

#include "Logic/Box2dBodyComponent.hpp"

namespace fug {

Box2dBodyComponent createPhysicsBox(b2BodyType type, b2Vec2 position, b2Vec2 halfSize,
    float density, float friction);


}

#endif // FUG_CREATE_PHYSICS_BOX_HPP
