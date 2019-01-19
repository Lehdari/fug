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

bool CollisionVolume::checkCollision(const CollisionVolume& other, Vec2f& normal)
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
                    Vec2f rx(other._volume.circle.r, 0.0f);
                    Vec2f ry(0.0f, other._volume.circle.r);
                    Vec2f p[] = { other._pos-rx,
                                  other._pos-ry,
                                  other._pos+rx,
                                  other._pos+ry };
                    Vec2f n[] = { Vec2f(-1.0f, 0.0f),
                                  Vec2f(0.0f, -1.0f),
                                  Vec2f(1.0f, 0.0f),
                                  Vec2f(0.0f, 1.0f) };
                    Vec2f c[] = { min1,
                                  Vec2f(min1(0), max1(1)),
                                  Vec2f(max1(0), min1(1)),
                                  max1 };
                    for (int i=0; i<4; ++i) {
                        if (p[i](0) > min1(0) && p[i](0) < max1(0) &&
                            p[i](1) > min1(1) && p[i](1) < max1(1)) {
                            normal = n[i];
                            return true;
                        }

                        if ((c[i]-other._pos).squaredNorm() <
                            other._volume.circle.r*other._volume.circle.r) {
                            normal = (c[i]-other._pos).normalized();
                            return true;
                        }
                    }
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
                    Vec2f rx(_volume.circle.r, 0.0f);
                    Vec2f ry(0.0f, _volume.circle.r);
                    Vec2f p[] = { _pos-rx, _pos-ry, _pos+rx, _pos+ry };
                    Vec2f n[] = { Vec2f(1.0f, 0.0f),
                                  Vec2f(0.0f, 1.0f),
                                  Vec2f(-1.0f, 0.0f),
                                  Vec2f(0.0f, -1.0f) };
                    Vec2f c[] = { min2,
                                  Vec2f(min2(0), max2(1)),
                                  Vec2f(max2(0), min2(1)),
                                  max2 };
                    for (int i=0; i<4; ++i) {
                        if (p[i](0) > min2(0) && p[i](0) < max2(0) &&
                            p[i](1) > min2(1) && p[i](1) < max2(1)) {
                            normal = n[i];
                            return true;
                        }

                        if ((_pos-c[i]).squaredNorm() <
                            _volume.circle.r*_volume.circle.r) {
                            normal = (_pos-c[i]).normalized();
                            return true;
                        }
                    }

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
