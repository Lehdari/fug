//
// Created by Lehdari on 9.1.2019.
//

#include "EventHandlers.hpp"
#include "Ecs.hpp"
#include "CollisionEvent.hpp"
#include "PhysicsComponent.hpp"
#include "SpriteComponent.hpp"
#include "EventComponent.hpp"

#include <cstdio> // TEMP


void EventHandler_Block_CollisionEvent::handleEvent(
    Ecs& ecs, const EntityId& eId, const CollisionEvent& event)
{
//    printf("Collision (Block): %lld and %lld\n", eId, event.entityId);
//    printf("Normal: [ %5.3f %5.3f ]\n", event.normal(0), event.normal(1));
    ecs.removeComponent<PhysicsComponent>(eId);
    ecs.removeComponent<SpriteComponent>(eId);
    ecs.removeComponent<EventComponent>(eId);
}

void EventHandler_Ball_CollisionEvent::handleEvent(
    Ecs& ecs, const EntityId& eId, const CollisionEvent& event)
{
//    printf("Collision (Ball): %lld and %lld\n", eId, event.entityId);
//    printf("Normal: [ %5.3f %5.3f ]\n", event.normal(0), event.normal(1));
    auto* phys = ecs.getComponent<PhysicsComponent>(eId);
    phys->vel = 2.0f*(event.normal.dot(-phys->vel))*event.normal+phys->vel;
}
