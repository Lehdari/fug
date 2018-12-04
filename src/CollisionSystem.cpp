//
// Created by Lehdari on 4.12.2018.
//

#include "CollisionSystem.hpp"

#include <Ecs.hpp>


CollisionSubSystem::CollisionSubSystem(void) :
    parentEId   (nullptr),
    parentPhys  (nullptr)
{
}

void CollisionSubSystem::operator()(const EntityId& eId, PhysicsComponent& phys)
{
    if (!parentEId || eId >= *parentEId || !parentPhys)
        return;

    if (parentPhys->colVol.checkCollision(phys.colVol)) {
        printf("Collision: %llu and %llu\n",
            (long long unsigned)(*parentEId), (long long unsigned)eId);
    }
}


CollisionSystem::CollisionSystem(Ecs& ecs) :
    _ecs    (ecs)
{
}

void CollisionSystem::operator()(const EntityId& eId, PhysicsComponent& phys)
{
    _subSystem.parentEId = &eId;
    _subSystem.parentPhys = &phys;

    _ecs.runSystem(_subSystem);
}
