//
// Project: fug
// File: Ecs.cpp
//
// Copyright (c) 2019 Miika 'Lehdari' Lehtimäki
// You may use, distribute and modify this code under the terms
// of the licence specified in file LICENSE which is distributed
// with this source code package.
//

#include "Ecs.hpp"


using namespace fug;


Ecs::Ecs() :
    _componentInitialized       (),
    _components                 (),
    _singletons                 (),
    _componentDeleters          (),
    _singletonDeleters          (),
    _componentsToAdd            (),
    _componentsToRemove         (),
    _componentDeferredAdders    (),
    _componentDeferredRemovers  (),
    _systemsRunning             (0)
{
}

Ecs::~Ecs()
{
    // Delete components and singletons
    for (int64_t i=0; i<TypeId::nComponents; ++i) {
        if (_componentDeleters[i])
            (_componentDeleters[i])(_components[i], _componentsToAdd[i]);
    }
    for (int64_t i=0; i<TypeId::nSingletons; ++i) {
        if (_singletonDeleters[i])
            (_singletonDeleters[i])(_singletons[i]);
    }
}

EntityId Ecs::getEmptyEntityId()
{
    // Search for an entity with all components disabled
    for (EntityId eId = 0; eId < _componentMasks.size(); ++eId) {
        if (_componentMasks[eId] == 0)
            return eId;
    }

    // No empty entity found
    return _componentMasks.size();
}

bool Ecs::entityExists(const EntityId& eId)
{
    if (_componentMasks.size() <= eId)
        return false;

    return _componentMasks[eId] != 0;
}

void Ecs::removeEntity(const EntityId& eId)
{
    if (_componentMasks.size() <= eId)
        return;

    if (_systemsRunning > 0) {
        for (uint64_t tId = 0; tId < TypeId::nComponents; ++tId) {
            if ((_componentMasks[eId] & ((uint64_t) 1 << tId)) > 0) {
                auto *v = static_cast<std::vector<EntityId> *>(_componentsToRemove[tId]);
                v->push_back(eId);
            }
        }
        return;
    }

    // Mark all components disabled for the entity
    _componentMasks[eId] = 0;
}
