//
// Created by Lehdari on 4.12.2018.
//

#include "CollisionVolume.hpp"


using namespace mm;


CollisionVolume::CollisionVolume(void) :
    _type   (UNKNOWN),
    _pos    (0.0f, 0.0f)
{
}

CollisionVolume::CollisionVolume(const CollisionVolume::Type& type,
                                 float p1, float p2, float p3, float p4) :
    _type   (type),
    _pos    (0.0f, 0.0f)
{
    switch (_type) {
        case BOX:
            _volume.box.min = Vec2f(p1, p2);
            _volume.box.max = Vec2f(p3, p4);
            break;
        case CIRCLE:
            _volume.circle.r = p1;
            break;
        default:
            break;
    }
}

CollisionVolume::CollisionVolume(const CollisionVolume& other) :
    _type   (other._type),
    _pos    (other._pos)
{
    switch (_type) {
        case BOX:
            _volume.box = other._volume.box;
            break;
        case CIRCLE:
            _volume.circle = other._volume.circle;
            break;
        default:
            _volume.unknown = other._volume.unknown;
            break;
    }
}

CollisionVolume& CollisionVolume::operator=(const CollisionVolume& other)
{
    _type = other._type;
    _pos = other._pos;

    switch (_type) {
        case BOX:
            _volume.box = other._volume.box;
            break;
        case CIRCLE:
            _volume.circle = other._volume.circle;
            break;
        default:
            _volume.unknown = other._volume.unknown;
            break;
    }

    return *this;
}

void CollisionVolume::setPosition(const mm::Vec2f& pos)
{
    _pos = pos;
}

bool CollisionVolume::checkCollision(const CollisionVolume& other)
{
    if (_type == UNKNOWN || other._type == UNKNOWN)
        return false;

    switch (_type) {
        case BOX: {
            Vec2f min1(_pos+_volume.box.min);
            Vec2f max1(_pos+_volume.box.max);

            switch (other._type) {
                case BOX: {
                    Vec2f min2(other._pos+other._volume.box.min);
                    Vec2f max2(other._pos+other._volume.box.max);
                    if (min1(0) < max2(0) && max1(0) > min2(0) &&
                        min1(1) < max2(1) && max1(1) > min2(1))
                        return true;
                }   break;
                case CIRCLE: {
                    // point nearest to box center
                    Vec2f p = other._pos +
                        (((max1+min1)*0.5f)-other._pos).normalized()*
                        other._volume.circle.r;
                    if (p(0) > min1(0) && p(0) < max1(0) &&
                        p(1) > min1(1) && p(1) < max1(1))
                        return true;
                }   break;
                default:
                    return false;
            }
        }   break;
        case CIRCLE:
            switch (other._type) {
                case BOX: {
                    Vec2f min2(other._pos+other._volume.box.min);
                    Vec2f max2(other._pos+other._volume.box.max);
                    Vec2f p = _pos + (((max2+min2)*0.5f)-_pos).normalized()*
                              _volume.circle.r;
                    if (p(0) > min2(0) && p(0) < max2(0) &&
                        p(1) > min2(1) && p(1) < max2(1))
                        return true;
                }   break;
                case CIRCLE: {
                    float d = (_pos-other._pos).norm();
                    if (d > _volume.circle.r+other._volume.circle.r)
                        return true;
                }   break;
                default:
                    return false;
            }
            break;
        default:
            return false;
    }

    return false;
}
