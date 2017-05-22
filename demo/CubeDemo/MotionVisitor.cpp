#include "MotionVisitor.hpp"
#include <iostream>

using namespace fug;

void MotionVisitor::operator() (MotionComponent& motion)
{
    induceCircularMotion(motion);
    motion.vel += motion.acc;
    motion.angvel *= motion.angacc;
}

void MotionVisitor::induceCircularMotion(MotionComponent& motion)
{
    static float theta = 0.02f;

    Matrix3Glf rot;
    rot << cos(theta),  0.f,        sin(theta),
           0.f,         cos(theta), 0.f,
           -sin(theta), 0.f,        cos(theta);

    motion.vel = rot * motion.vel;
}
