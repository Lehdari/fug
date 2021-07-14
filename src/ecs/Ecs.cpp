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
    _deferredOperations         (),
    _maxDeferredEntityId        (-1),
    _systemsRunning             (0)
{
}

Ecs::~Ecs()
{
    // Delete components and singletons
    for (int64_t i=0; i<TypeId::nComponents; ++i) {
        if (_componentDeleters[i])
            (_componentDeleters[i])(_components[i], _deferredComponents[i]);
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
    return std::max((EntityId)_componentMasks.size(), _maxDeferredEntityId+1);
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

    if (_systemsRunning > 0)
        deferEntityRemove(eId);

    // Mark all components disabled for the entity
    _componentMasks[eId] = 0;
}


inline void Ecs::deferEntityRemove(const EntityId& eId)
{
    _deferredOperations.emplace_back(DeferredOperation::ENTITY_REMOVE, eId);
}

void Ecs::executeDeferredOperations()
{
    for (auto& o : _deferredOperations) {
        switch (o.type) {
            case DeferredOperation::COMPONENT_ADD:
                (this->*o.operation.componentAdd)(o.entityId, o.componentId);
                break;

            case DeferredOperation::COMPONENT_REMOVE:
                (this->*o.operation.componentRemove)(o.entityId);
                break;

            case DeferredOperation::ENTITY_REMOVE:
                if (_componentMasks.size() <= o.entityId)
                    continue;

                // Mark all components as disabled for the entity
                _componentMasks[o.entityId] &= 0;
                break;
        }
    }

    _deferredOperations.clear();
    _maxDeferredEntityId = -1;
}
