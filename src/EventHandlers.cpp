//
// Created by Lehdari on 9.1.2019.
//

#include "EventHandlers.hpp"
#include "Ecs.hpp"
#include "CollisionEvent.hpp"

#include <cstdio> // TEMP


void EventHandler_Block_CollisionEvent::handleEvent(
    Ecs& ecs, const EntityId& eId, const CollisionEvent& event)
{
    printf("Collision (Block): %lld and %lld\n", eId, event.entityId);
}

void EventHandler_Ball_CollisionEvent::handleEvent(
    Ecs& ecs, const EntityId& eId, const CollisionEvent& event)
{
    printf("Collision (Ball): %lld and %lld\n", eId, event.entityId);
}