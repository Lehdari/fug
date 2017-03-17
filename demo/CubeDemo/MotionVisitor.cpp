#include "MotionVisitor.hpp"
#include <iostream>

using namespace fug;

void MotionVisitor::operator() (MotionComponent& motion, TransformComponent& trans)
{
    induceCircularMotion(motion); // for demo

    motion.vel += motion.acc;
    motion.angvel *= motion.angacc;
    trans.position += motion.vel;
    trans.orientation *= motion.angvel;
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
