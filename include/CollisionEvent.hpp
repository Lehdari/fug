//
// Created by Lehdari on 9.1.2019.
//

#ifndef ECSTESTGAME_COLLISIONEVENT_HPP
#define ECSTESTGAME_COLLISIONEVENT_HPP


#include <Types.hpp>
#include <vec2f.h>


struct CollisionEvent {
    EntityId    entityId;
    vm::vec2f   normal;

    CollisionEvent(const EntityId& eId,
                   const vm::vec2f& normal = vm::vec2f(0.0f, 0.0f)) :
        entityId    (eId),
        normal      (normal)
    {}
};


#endif //ECSTESTGAME_COLLISIONEVENT_HPP
