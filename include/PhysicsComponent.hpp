//
// Created by lehdari on 3.11.2018.
//

#ifndef ECSTESTGAME_PHYSICSCOMPONENT_HPP
#define ECSTESTGAME_PHYSICSCOMPONENT_HPP


#include <MathTypes.hpp>

#include "CollisionVolume.hpp"


struct PhysicsComponent {
    PhysicsComponent(mm::Vec2f pos, mm::Vec2f vel,
                     const CollisionVolume& colVol = CollisionVolume()) :
        pos     (pos),
        vel     (vel),
        colVol  (colVol)
    {
    }

    mm::Vec2f       pos;
    mm::Vec2f       vel;
    CollisionVolume colVol;
};


#endif //ECSTESTGAME_PHYSICSCOMPONENT_HPP
