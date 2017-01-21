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
    bodyDef.position = def.position;
    auto body = worldRes->world->CreateBody(&bodyDef);
    b2FixtureDef fixtureDef;
    fixtureDef.shape = def.shape;
    fixtureDef.density = 2.f;//def.density;
    fixtureDef.friction = 0.0f;//def.friction;
    auto fixture = body->CreateFixture(&fixtureDef);
    fixture->SetDensity(2.f);
    body->ResetMassData();
    return Box2dBodyComponent(body);
}

}
