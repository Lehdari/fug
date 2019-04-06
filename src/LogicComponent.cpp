//
// Created by Lehdari on 6.4.2019.
//

#include "LogicComponent.hpp"


LogicComponent::LogicComponent() :
    _logic          (nullptr),
    _logicDeleter   (nullptr)
{
}

LogicComponent::~LogicComponent()
{
    if (_logicDeleter)
        _logicDeleter(_logic);
}
