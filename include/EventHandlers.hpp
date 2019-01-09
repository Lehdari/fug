//
// Created by Lehdari on 9.1.2019.
//

#ifndef ECSTESTGAME_EVENTHANDLERS_HPP
#define ECSTESTGAME_EVENTHANDLERS_HPP


#include <vector>

#include "EventHandler.hpp"
#include "CollisionEvent.hpp"


EVENT_HANDLER(EventHandler_Block_CollisionEvent, CollisionEvent);
EVENT_HANDLER(EventHandler_Ball_CollisionEvent, CollisionEvent);


#endif //ECSTESTGAME_EVENTHANDLERS_HPP
