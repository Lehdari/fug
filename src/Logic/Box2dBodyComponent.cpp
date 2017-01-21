#include <Eigen/Geometry>
#include "Logic/Box2dBodyComponent.hpp"


using namespace fug;

b2World* Box2dBodyComponent::world = nullptr;

Box2dBodyComponent::Box2dBodyComponent()
{}

Box2dBodyComponent::Box2dBodyComponent(b2Body* body) :
    body(body)
{}

Box2dBodyComponent::Box2dBodyComponent(Box2dBodyComponent&& other) {
    body = other.body;
    other.body = nullptr;
}

Box2dBodyComponent& Box2dBodyComponent::operator=(fug::Box2dBodyComponent &&other) {
    body = other.body;
    other.body = nullptr;
    return *this;
}

Box2dBodyComponent::~Box2dBodyComponent() {
    if(world) {
        world->DestroyBody(body);
    }
}
