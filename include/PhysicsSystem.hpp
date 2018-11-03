//
// Created by lehdari on 3.11.2018.
//

#ifndef ECSTESTGAME_PHYSICSSYSTEM_HPP
#define ECSTESTGAME_PHYSICSSYSTEM_HPP


#include <System.hpp>
#include "PhysicsComponent.hpp"


TECS_SYSTEM(PhysicsSystem, PhysicsComponent) {
public:
    void operator()(PhysicsComponent& c);
};


#endif //ECSTESTGAME_PHYSICSSYSTEM_HPP
