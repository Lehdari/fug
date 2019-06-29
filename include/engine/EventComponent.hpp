//
// Project: fug
// File: EventComponent.hpp
//
// Copyright (c) 2019 Miika 'Lehdari' Lehtimäki
// You may use, distribute and modify this code under the terms
// of the licence specified in file LICENSE which is distributed
// with this source code package.
//

#ifndef FUG_ENGINE_EVENTCOMPONENT_HPP
#define FUG_ENGINE_EVENTCOMPONENT_HPP


#include "EventTypeId.hpp"
#include "EventHandler.hpp"

#include <Ecs.hpp>
#include <unordered_map>
#include <vector>


class EventComponent {
public:
    friend class EventSystem;

    template <typename T_Handler>
    void addHandler();

private:
    using Handler = void(*)(Ecs& ecs, const EntityId& eId, void* events);
    using LogicHandler = void(*)(Ecs& ecs, const EntityId& eId, void* logic, void* events);

    std::unordered_map<int64_t, Handler>        _handlers;
    std::unordered_map<int64_t, LogicHandler>   _logicHandlers;
};


DECLARE_COMPONENT_TEMPLATES(EventComponent);


template <typename T_Handler>
void EventComponent::addHandler()
{
    auto etId = EventTypeId::typeId<typename T_Handler::EventType>();
    if constexpr (T_Handler::hasLogic) {
        _logicHandlers[etId] = &EventLogicHandler<T_Handler,
            typename T_Handler::EventType, typename T_Handler::LogicType>::handleEvents;
    }
    else {
        _handlers[etId] = &EventHandler<T_Handler, typename T_Handler::EventType>::handleEvents;
    }
}


#endif //FUG_ENGINE_EVENTCOMPONENT_HPP
