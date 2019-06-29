//
// Project: fug
// File: LogicSystem.hpp
//
// Copyright (c) 2019 Miika 'Lehdari' Lehtimäki
// You may use, distribute and modify this code under the terms
// of the licence specified in file LICENSE which is distributed
// with this source code package.
//

#ifndef FUG_ENGINE_LOGICSYSTEM_HPP
#define FUG_ENGINE_LOGICSYSTEM_HPP


#include <System.hpp>

#include "LogicComponent.hpp"


TECS_SYSTEM(LogicSystem, LogicComponent) {
public:
    LogicSystem(Ecs& ecs);

    void operator()(const EntityId& eId, LogicComponent& ec);

private:
    Ecs&    _ecs;
};


#endif //FUG_ENGINE_LOGICSYSTEM_HPP
