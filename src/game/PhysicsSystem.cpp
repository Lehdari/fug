//
// Created by lehdari on 3.11.2018.
//

#include <game/PhysicsSystem.hpp>


void PhysicsSystem::operator()(const EntityId& eId, PhysicsComponent& c)
{
    c.pos += c.vel;
    c.colVol.setPosition(c.pos);
}
