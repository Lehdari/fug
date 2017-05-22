#include "Logic/TransformComponent.hpp"

using namespace fug;

TransformComponent::TransformComponent(Vector3Glf const& pos, QuaternionGlf const& ori, Vector3Glf const& sca) :
    position(pos), orientation(ori), scale(sca)
{
    transform << 1.f, 0.f, 0.f, 0.f,
                 0.f, 1.f, 0.f, 0.f,
                 0.f, 0.f, 1.f, 0.f,
                 0.f, 0.f, 0.f, 1.f;
}
