#include "Logic/createBox2dBody.hpp"
#include "Logic/Box2dWorld.hpp"
#include "Core/ResourceManager.hpp"
#include <iostream>

namespace fug {

Box2dBodyComponent createBox2dBody(Box2dBodyDefinition def)
{
    auto worldRes = FUG_RESOURCE_MANAGER.getResource<Box2dWorld>(2);
    std::cerr << worldRes->world << std::endl;
    b2BodyDef bodyDef;
    bodyDef.type = def.type;
    bodyDef.position = def.position;
    bodyDef.awake = true;
    bodyDef.active = true;
    bodyDef.bullet = false;
    bodyDef.gravityScale = 1.f;
    auto body = worldRes->world->CreateBody(&bodyDef);
    b2FixtureDef fixtureDef;
    fixtureDef.shape = def.shape;
    fixtureDef.density = def.density;
    fixtureDef.friction = def.friction;
    auto fixture = body->CreateFixture(&fixtureDef);
    return Box2dBodyComponent(body);
}

}
