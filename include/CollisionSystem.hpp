//
// Created by Lehdari on 4.12.2018.
//

#ifndef ECSTESTGAME_COLLISIONSYSTEM_HPP
#define ECSTESTGAME_COLLISIONSYSTEM_HPP


#include <System.hpp>
#include "PhysicsComponent.hpp"


class Ecs;


TECS_SYSTEM(CollisionSubSystem, PhysicsComponent) {
    CollisionSubSystem(void);

    void operator()(const EntityId& eId, PhysicsComponent& phys);

    /// Pointers to references passed to parent CollisionSystem
    const EntityId*     parentEId;
    PhysicsComponent*   parentPhys;
};


TECS_SYSTEM(CollisionSystem, PhysicsComponent) {
    CollisionSystem(Ecs& ecs);

    void operator()(const EntityId& eId, PhysicsComponent& phys);

private:
    Ecs&                _ecs;
    CollisionSubSystem  _subSystem;
};


#endif //ECSTESTGAME_COLLISIONSYSTEM_HPP
