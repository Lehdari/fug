//
// Created by Lehdari on 4.12.2018.
//

#ifndef ECSTESTGAME_COLLISIONVOLUME_HPP
#define ECSTESTGAME_COLLISIONVOLUME_HPP


#include <vec2f.h>


class CollisionVolume {
public:
    enum Type {
        UNKNOWN = 0,
        BOX     = 1,
        CIRCLE  = 2
    };

    /** Construct collision volume
    *   type: type of the collision volume (BOX or CIRCLE)
    *   p1-p4:
    *       for BOX type:
    *           p1: xMin
    *           p2: yMin
    *           p3: xMax
    *           p4: yMax
    *      for CIRCLE type:
    *           p1: radius
    *           p2-p3: not used
    **/
    CollisionVolume(void);
    CollisionVolume(const Type& type,
                    float p1, float p2 = 0.0f, float p3 = 0.0f, float p4 = 0.0f);

    CollisionVolume(const CollisionVolume& other);
    CollisionVolume(CollisionVolume&&) = delete;
    CollisionVolume& operator=(const CollisionVolume& other);
    CollisionVolume& operator=(CollisionVolume&&) = delete;

    ~CollisionVolume() = default;

    void setPosition(const vm::vec2f& pos);

    bool checkCollision(const CollisionVolume& other, vm::vec2f& normal);

private:
    Type        _type;
    vm::vec2f   _pos;

    union Volume {
        struct Unknown {
        }   unknown;
        struct Box {
            vm::vec2f   min;
            vm::vec2f   max;
        }   box;
        struct Circle {
            float   r;
        }   circle;

        Volume(void) :
            unknown() {}
    }   _volume;
};


#endif //ECSTESTGAME_COLLISIONVOLUME_HPP
