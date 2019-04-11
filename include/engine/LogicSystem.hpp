//
// Created by Lehdari on 6.4.2019.
//

#ifndef ECSTESTGAME_LOGICSYSTEM_HPP
#define ECSTESTGAME_LOGICSYSTEM_HPP


#include <System.hpp>

#include "LogicComponent.hpp"


TECS_SYSTEM(LogicSystem, LogicComponent) {
public:
    LogicSystem(Ecs& ecs);

    void operator()(const EntityId& eId, LogicComponent& ec);

private:
    Ecs&    _ecs;
};


#endif //ECSTESTGAME_LOGICSYSTEM_HPP
