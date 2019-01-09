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
    std::unordered_map<int64_t, void(*)(Ecs& ecs, const EntityId&, void*)> _handlers;
};


template <typename T_Handler>
void EventComponent::addHandler()
{
    auto etId = EventTypeId::typeId<typename T_Handler::EventType>();
    _handlers[etId] = &EventHandler<T_Handler, typename T_Handler::EventType>::handleEvents;
}


#endif //ECSTESTGAME_EVENTCOMPONENT_HPP
