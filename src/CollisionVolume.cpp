//
// Created by Lehdari on 4.12.2018.
//

#include "CollisionVolume.hpp"


using namespace vm;


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
            _volume.box.min = vec2f(p1, p2);
            _volume.box.max = vec2f(p3, p4);
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

void CollisionVolume::setPosition(const vm::vec2f& pos)
{
    _pos = pos;
}

bool CollisionVolume::checkCollision(const CollisionVolume& other, vec2f& normal)
{
    if (_type == UNKNOWN || other._type == UNKNOWN)
        return false;

    switch (_type) {
        case BOX: {
            vec2f min1(_pos+_volume.box.min);
            vec2f max1(_pos+_volume.box.max);

            switch (other._type) {
                case BOX: {
                    vec2f min2(other._pos+other._volume.box.min);
                    vec2f max2(other._pos+other._volume.box.max);
                    if (min1.x < max2.x && max1.x > min2.x &&
                        min1.y < max2.y && max1.y > min2.y)
                        return true;
                }   break;
                case CIRCLE: {
                    vec2f rx(other._volume.circle.r, 0.0f);
                    vec2f ry(0.0f, other._volume.circle.r);
                    vec2f p[] = { other._pos-rx,
                                  other._pos-ry,
                                  other._pos+rx,
                                  other._pos+ry };
                    vec2f n[] = { vec2f(-1.0f, 0.0f),
                                  vec2f(0.0f, -1.0f),
                                  vec2f(1.0f, 0.0f),
                                  vec2f(0.0f, 1.0f) };
                    vec2f c[] = { min1,
                                  vec2f(min1.x, max1.y),
                                  vec2f(max1.x, min1.y),
                                  max1 };
                    for (int i=0; i<4; ++i) {
                        if (p[i].x > min1.x && p[i].x < max1.x &&
                            p[i].y > min1.y && p[i].y < max1.y) {
                            normal = n[i];
                            return true;
                        }

                        if ((c[i]-other._pos).norm2() <
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
                    vec2f min2(other._pos+other._volume.box.min);
                    vec2f max2(other._pos+other._volume.box.max);
                    vec2f rx(_volume.circle.r, 0.0f);
                    vec2f ry(0.0f, _volume.circle.r);
                    vec2f p[] = { _pos-rx, _pos-ry, _pos+rx, _pos+ry };
                    vec2f n[] = { vec2f(1.0f, 0.0f),
                                  vec2f(0.0f, 1.0f),
                                  vec2f(-1.0f, 0.0f),
                                  vec2f(0.0f, -1.0f) };
                    vec2f c[] = { min2,
                                  vec2f(min2.x, max2.y),
                                  vec2f(max2.x, min2.y),
                                  max2 };
                    for (int i=0; i<4; ++i) {
                        if (p[i].x > min2.x && p[i].x < max2.x &&
                            p[i].y > min2.y && p[i].y < max2.y) {
                            normal = n[i];
                            return true;
                        }

                        if ((_pos-c[i]).norm2() <
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
