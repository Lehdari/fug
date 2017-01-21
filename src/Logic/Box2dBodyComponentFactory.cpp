#include "Logic/Box2dBodyComponentFactory.hpp"
#include "Logic/Box2dWorld.hpp"
#include "Core/ResourceManager.hpp"

namespace fug {

Box2dBodyComponent Box2dBodyComponentFactory(b2BodyDef bodyDef, b2FixtureDef fixtureDef)
{
    auto worldRes = FUG_RESOURCE_MANAGER.getResource<Box2dWorld>(1);
    auto body = worldRes->world.CreateBody(&bodyDef);
    body->CreateFixture(&fixtureDef);
    return Box2dBodyComponent(body);
}

}
