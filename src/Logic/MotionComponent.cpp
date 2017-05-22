#include "Logic/MotionComponent.hpp"

using namespace fug;

MotionComponent::MotionComponent(Vector3Glf const& vel,
                                 Vector3Glf const& acc,
                                 QuaternionGlf const& angvel,
                                 QuaternionGlf const& angacc) :
    vel(vel), acc(acc), angvel(angvel), angacc(angacc)
{}
