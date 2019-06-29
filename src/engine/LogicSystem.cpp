//
// Project: fug
// File: LogicSystem.cpp
//
// Copyright (c) 2019 Miika 'Lehdari' Lehtimäki
// You may use, distribute and modify this code under the terms
// of the licence specified in file LICENSE which is distributed
// with this source code package.
//

#include <engine/LogicSystem.hpp>


using namespace fug;


LogicSystem::LogicSystem(Ecs& ecs) :
    _ecs    (ecs)
{
}

void LogicSystem::operator()(const EntityId& eId, LogicComponent& lc)
{
    if (lc._logicExecutor)
        lc._logicExecutor(lc._logic, _ecs, eId);
}
