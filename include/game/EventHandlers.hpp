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
EVENT_HANDLER(EventHandler_BottomWall_CollisionEvent, CollisionEvent);

struct LaunchEvent {};
DECLARE_EVENT_TEMPLATES(LaunchEvent);
EVENT_LOGIC_HANDLER(EventHandler_Ball_LaunchEvent, LaunchEvent, Logic_Ball);

struct BreakEvent {};
DECLARE_EVENT_TEMPLATES(BreakEvent);
EVENT_LOGIC_HANDLER(EventHandler_GameManager_BreakEvent, BreakEvent, Logic_GameManager);

struct LoseLifeEvent {};
DECLARE_EVENT_TEMPLATES(LoseLifeEvent);
EVENT_LOGIC_HANDLER(
    EventHandler_GameManager_LoseLifeEvent,
    LoseLifeEvent, Logic_GameManager);
EVENT_LOGIC_HANDLER(
    EventHandler_Ball_LoseLifeEvent,
    LoseLifeEvent, Logic_Ball);


#endif //ECSTESTGAME_EVENTHANDLERS_HPP
