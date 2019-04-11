//
// Created by Lehdari on 8.1.2019.
//

#ifndef ECSTESTGAME_EVENTCOMPONENT_HPP
#define ECSTESTGAME_EVENTCOMPONENT_HPP


#include "EventTypeId.hpp"
#include "EventHandler.hpp"

#include <unordered_map>
#include <vector>


class Ecs;


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


#endif //ECSTESTGAME_EVENTCOMPONENT_HPP
