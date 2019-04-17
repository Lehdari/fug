//
// Created by Lehdari on 9.1.2019.
//

#ifndef ECSTESTGAME_EVENTHANDLERS_HPP
#define ECSTESTGAME_EVENTHANDLERS_HPP


#include <vector>
#include <engine/EventHandler.hpp>
#include <engine/EventTypeId.hpp>

#include "CollisionEvent.hpp"
#include "Logics.hpp"


EVENT_HANDLER(EventHandler_Block_CollisionEvent, CollisionEvent);
EVENT_HANDLER(EventHandler_Ball_CollisionEvent, CollisionEvent);

struct LaunchEvent {};
DECLARE_EVENT_TEMPLATES(LaunchEvent);
EVENT_LOGIC_HANDLER(EventHandler_Ball_LaunchEvent, LaunchEvent, Logic_Ball);

struct BreakEvent {};
DECLARE_EVENT_TEMPLATES(BreakEvent);
EVENT_LOGIC_HANDLER(EventHandler_GameManager_BreakEvent, BreakEvent, Logic_GameManager);


#endif //ECSTESTGAME_EVENTHANDLERS_HPP
