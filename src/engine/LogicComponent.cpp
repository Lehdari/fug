//
// Created by Lehdari on 6.4.2019.
//

#include <engine/LogicComponent.hpp>


DEFINE_COMPONENT_TEMPLATES(LogicComponent);


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
