//
// Created by Lehdari on 4.12.2018.
//

#ifndef ECSTESTGAME_COLLISIONSYSTEM_HPP
#define ECSTESTGAME_COLLISIONSYSTEM_HPP


#include <System.hpp>
#include "PhysicsComponent.hpp"


class Ecs;
class EventSystem;


TECS_SYSTEM(CollisionSubSystem, PhysicsComponent) {
public:
    friend class CollisionSystem;

    CollisionSubSystem(EventSystem& eventSystem);

    void operator()(const EntityId& eId, PhysicsComponent& phys);

private:
    EventSystem&        _eventSystem;

    /// Pointers to references passed to parent CollisionSystem
    const EntityId*     _parentEId;
    PhysicsComponent*   _parentPhys;
};


TECS_SYSTEM(CollisionSystem, PhysicsComponent) {
public:
    CollisionSystem(Ecs& ecs, EventSystem& eventSystem);

    void operator()(const EntityId& eId, PhysicsComponent& phys);

private:
    Ecs&                _ecs;
    CollisionSubSystem  _subSystem;
};


#endif //ECSTESTGAME_COLLISIONSYSTEM_HPP
