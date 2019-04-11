//
// Created by Lehdari on 4.12.2018.
//

#include <game/CollisionSystem.hpp>
#include <game/CollisionEvent.hpp>
#include <engine/EventSystem.hpp>
#include <Ecs.hpp>


using namespace vm;


CollisionSubSystem::CollisionSubSystem(EventSystem& eventSystem) :
    _eventSystem(eventSystem),
    _parentEId  (nullptr),
    _parentPhys (nullptr)
{
}

void CollisionSubSystem::operator()(const EntityId& eId, PhysicsComponent& phys)
{
    if (!_parentEId || eId == *_parentEId || !_parentPhys)
        return;

    vec2f normal;
    if (_parentPhys->colVol.checkCollision(phys.colVol, normal)) {
        _eventSystem.sendEvent(*_parentEId, CollisionEvent(eId, normal));
    }
}


CollisionSystem::CollisionSystem(Ecs& ecs, EventSystem& eventSystem) :
    _ecs        (ecs),
    _subSystem  (eventSystem)
{
}

void CollisionSystem::operator()(const EntityId& eId, PhysicsComponent& phys)
{
    _subSystem._parentEId = &eId;
    _subSystem._parentPhys = &phys;

    _ecs.runSystem(_subSystem);
}
