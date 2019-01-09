//
// Created by Lehdari on 9.1.2019.
//

#include "EventHandlers.hpp"
#include "CollisionEvent.hpp"

#include <cstdio> // TEMP


void EventHandler_Block_CollisionEvent::handleEvent(
    const EntityId& eId, const CollisionEvent& event)
{
    printf("Collision: %lld and %lld\n", eId, event.entityId);
}