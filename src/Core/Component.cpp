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

Component& Component::operator=(Component&& other)
{
    if (this == &other)
        return *this;
    _entityId = other._entityId;
    other._entityId = 0;
    return *this;
}

CId Component::_typeId = CId();
