//
// Created by Lehdari on 4.12.2018.
//

#include "CollisionSystem.hpp"
#include "EventSystem.hpp"
#include "CollisionEvent.hpp"

#include <Ecs.hpp>


CollisionSubSystem::CollisionSubSystem(EventSystem& eventSystem) :
    _eventSystem(eventSystem),
    _parentEId  (nullptr),
    _parentPhys (nullptr)
{
}

void CollisionSubSystem::operator()(const EntityId& eId, PhysicsComponent& phys)
{
    if (!_parentEId || eId >= *_parentEId || !_parentPhys)
        return;

    if (_parentPhys->colVol.checkCollision(phys.colVol)) {
        _eventSystem.sendEvent(*_parentEId, CollisionEvent(eId));
        _eventSystem.sendEvent(eId, CollisionEvent(*_parentEId));
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
