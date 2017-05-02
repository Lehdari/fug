#include "TransformVisitor.hpp"
#include "Core/EventManager.hpp"

using namespace fug;

void TransformVisitor::operator() (MotionComponent& motion, TransformComponent& trans)
{
    trans.transform(0,3) += motion.vel(0);
    trans.transform(1,3) += motion.vel(1);
    trans.transform(2,3) += motion.vel(2);

    motion.angvel.normalize();
    auto qr = motion.angvel.toRotationMatrix();

    Matrix4Glf rot;
    rot << qr(0,0), qr(0,1), qr(0,2),  0.f,
           qr(1,0), qr(1,1), qr(1,2),  0.f,
           qr(2,0), qr(2,1), qr(2,2),  0.f,
              0.f,     0.f,     0.f,   1.f;    

    trans.transform *= rot;
}
