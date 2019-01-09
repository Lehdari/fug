//
// Created by Lehdari on 9.1.2019.
//

#include "EventHandlers.hpp"
#include "CollisionEvent.hpp"

#include <cstdio> // TEMP


void EventHandler_Block_CollisionEvent::handleEvent(const CollisionEvent& e)
{
    printf("Collision: %lld\n", e.entityId);
}