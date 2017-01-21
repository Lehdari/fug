#include <Eigen/Geometry>
#include "Logic/Box2dBodyComponent.hpp"


using namespace fug;

b2World* Box2dBodyComponent::world = nullptr;

Box2dBodyComponent::Box2dBodyComponent(b2Body* body) :
    body(body)
{}

Box2dBodyComponent::~Box2dBodyComponent() {
    if(world) {
        world->DestroyBody(body);
    }
}
