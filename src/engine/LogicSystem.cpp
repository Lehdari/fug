//
// Created by Lehdari on 6.4.2019.
//

#include <engine/LogicSystem.hpp>


LogicSystem::LogicSystem(Ecs& ecs) :
    _ecs    (ecs)
{
}

void LogicSystem::operator()(const EntityId& eId, LogicComponent& lc)
{
    if (lc._logicExecutor)
        lc._logicExecutor(lc._logic, _ecs, eId);
}
