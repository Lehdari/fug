#include "BeatComponent.hpp"

using namespace fug;

BeatComponent::BeatComponent(ReactType behavior, float strength, float release) :
   behavior(behavior), strength(strength), release(release), _delta(0.f)
{}
