//
// Created by lehdari on 3.11.2018.
//

#include "PhysicsSystem.hpp"


void PhysicsSystem::operator()(PhysicsComponent& c)
{
    c.pos += c.vel;
}
