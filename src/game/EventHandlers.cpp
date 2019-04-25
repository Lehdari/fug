//
// Created by Lehdari on 9.1.2019.
//

#include <game/EventHandlers.hpp>
#include <Ecs.hpp>
#include <engine/EventComponent.hpp>
#include <game/CollisionEvent.hpp>
#include <game/PhysicsComponent.hpp>
#include <game/SpriteComponent.hpp>
#include <game/SystemComponent.hpp>


DEFINE_EVENT_TEMPLATES(LaunchEvent);
DEFINE_EVENT_TEMPLATES(BreakEvent);
DEFINE_EVENT_TEMPLATES(LoseLifeEvent);


void EventHandler_Block_CollisionEvent::handleEvent(
    Ecs& ecs, const EntityId& eId, const CollisionEvent& event)
{
    auto* sc = ecs.getSingleton<SystemComponent>();
    sc->eventSystem->broadcastEvent(BreakEvent());

    ecs.removeComponent<PhysicsComponent>(eId);
    ecs.removeComponent<SpriteComponent>(eId);
    ecs.removeComponent<EventComponent>(eId);
}

void EventHandler_Ball_CollisionEvent::handleEvent(
    Ecs& ecs, const EntityId& eId, const CollisionEvent& event)
{
    auto* phys = ecs.getComponent<PhysicsComponent>(eId);
    phys->vel = 2.0f*dot(event.normal, -phys->vel)*event.normal+phys->vel;
}

void EventHandler_Ball_LaunchEvent::handleEvent(
    Ecs& ecs, const EntityId& eId, Logic_Ball& logic, const LaunchEvent& event)
{
    ecs.getComponent<PhysicsComponent>(eId)->vel = vm::vec2f(2.0f, -5.0f);
    logic._followPaddle = false;
}

void EventHandler_GameManager_BreakEvent::handleEvent(
    Ecs& ecs, const EntityId& eId, Logic_GameManager& logic,
    const BreakEvent& event)
{
    ++logic._points;
}
