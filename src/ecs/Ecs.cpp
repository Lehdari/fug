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
