//
// Project: fug
// File: LogicComponent.cpp
//
// Copyright (c) 2019 Miika 'Lehdari' Lehtimäki
// You may use, distribute and modify this code under the terms
// of the licence specified in file LICENSE which is distributed
// with this source code package.
//

#include <engine/LogicComponent.hpp>


using namespace fug;


FUG_DEFINE_COMPONENT_TEMPLATES(LogicComponent);


LogicComponent::LogicComponent() :
    _logic          (nullptr),
    _logicExecutor  (nullptr),
    _logicDeleter   (nullptr),
    _logicCopier    (nullptr)
{
}

LogicComponent::LogicComponent(const LogicComponent& other) :
    LogicComponent()
{
    if (other._logicCopier)
        other._logicCopier(other._logic, *this);
}

LogicComponent::LogicComponent(LogicComponent&& other) :
    _logic          (other._logic),
    _logicExecutor  (other._logicExecutor),
    _logicDeleter   (other._logicDeleter),
    _logicCopier    (other._logicCopier)
{
    other._logic         = nullptr;
    other._logicExecutor = nullptr;
    other._logicDeleter  = nullptr;
    other._logicCopier   = nullptr;
}

LogicComponent LogicComponent::operator=(const LogicComponent& other)
{
    if (_logicDeleter)
        _logicDeleter(_logic);

    if (other._logicCopier)
        other._logicCopier(other._logic, *this);
}

LogicComponent LogicComponent::operator=(LogicComponent&& other)
{
    if (_logicDeleter)
        _logicDeleter(_logic);

    _logic         = other._logic;
    _logicExecutor = other._logicExecutor;
    _logicDeleter  = other._logicDeleter;
    _logicCopier   = other._logicCopier;

    other._logic         = nullptr;
    other._logicExecutor = nullptr;
    other._logicDeleter  = nullptr;
    other._logicCopier   = nullptr;
}

LogicComponent::~LogicComponent()
{
    if (_logicDeleter)
        _logicDeleter(_logic);
}
