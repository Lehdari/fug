//
// Created by Lehdari on 9.1.2019.
//

#ifndef ECSTESTGAME_COLLISIONEVENT_HPP
#define ECSTESTGAME_COLLISIONEVENT_HPP


#include <Types.hpp>


struct CollisionEvent {
    EntityId    entityId;

    CollisionEvent(const EntityId& eId) :
        entityId    (eId)
    {}
};


#endif //ECSTESTGAME_COLLISIONEVENT_HPP
