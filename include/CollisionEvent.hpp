//
// Created by Lehdari on 9.1.2019.
//

#ifndef ECSTESTGAME_COLLISIONEVENT_HPP
#define ECSTESTGAME_COLLISIONEVENT_HPP


#include <Types.hpp>
#include <MathTypes.hpp>


struct CollisionEvent {
    EntityId    entityId;
    mm::Vec2f   normal;

    CollisionEvent(const EntityId& eId,
                   const mm::Vec2f& normal = mm::Vec2f(0.0f, 0.0f)) :
        entityId    (eId),
        normal      (normal)
    {}
};


#endif //ECSTESTGAME_COLLISIONEVENT_HPP
