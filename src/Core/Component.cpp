#include "Core/Component.hpp"


using namespace fug;

Component::Component(Component&& other) :
    _entityId(other._entityId)
{
    other._entityId = 0;
}

Component::Component(void) :
    _entityId()
{
}

CId Component::_typeId = CId();
