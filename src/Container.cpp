#include "Container.hpp"


uint64_t Container::typeIdCounter = 0;


Container::Container() :
    _entityId   (0)
{
}

Container::~Container()
{
    for (auto& cd : _componentDeleters)
        cd();
}

uint64_t Container::addEntity()
{
    return ++_entityId;
}
