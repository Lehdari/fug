#include "Logic/Box2dWorld.hpp"
#include "Logic/Box2dBodyComponent.hpp"


using namespace fug;


Box2dWorld::Box2dWorld(void) :
    world(nullptr)
{
}

Box2dWorld::Box2dWorld(Box2dWorld&& other) :
    world(other.world)
{
    if (other.world != nullptr)
        other.world = nullptr;
}

Box2dWorld& Box2dWorld::operator=(Box2dWorld&& other)
{
    world = other.world;
    if (other.world != nullptr)
        other.world = nullptr;

    return *this;
}

Box2dWorld::~Box2dWorld(void)
{
    if (world != nullptr) {
        delete world;
        world = nullptr;
        Box2dBodyComponent::world = nullptr;
    }
}
