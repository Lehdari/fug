#include "TransformVisitor.hpp"
#include "Core/EventManager.hpp"

#include <iostream>

using namespace fug;

void TransformVisitor::operator() (TransformComponent& trans)
{
    static Matrix4Glf T, R, S;

    T.diagonal() << 1.f, 1.f, 1.f, 1.f;
    T(0,3) = trans.position(0);
    T(1,3) = trans.position(1);
    T(2,3) = trans.position(2);

    trans.orientation.normalize();
    auto qr = trans.orientation.toRotationMatrix();
    R << qr(0,0), qr(0,1), qr(0,2),  0.f,
         qr(1,0), qr(1,1), qr(1,2),  0.f,
         qr(2,0), qr(2,1), qr(2,2),  0.f,
            0.f,     0.f,     0.f,   1.f;

    S(0,0) = trans.scale(0);
    S(1,1) = trans.scale(1);
    S(2,2) = trans.scale(2);
    S(3,3) = 1.f;

    trans.transform = T * R * S;
}
