//
// Created by Lehdari on 8.1.2019.
//

#ifndef ECSTESTGAME_EVENTSYSTEM_HPP
#define ECSTESTGAME_EVENTSYSTEM_HPP


#include <functional>

#include <System.hpp>
#include <Ecs.hpp>

#include "EventComponent.hpp"


TECS_SYSTEM(EventSystem, EventComponent) {
public:
    EventSystem(Ecs& ecs);
    ~EventSystem();

    void operator()(const EntityId& eId, EventComponent& ec);

    template <typename T_Event>
    void sendEvent(const EntityId& eId, const T_Event& event);

private:
    Ecs&    _ecs;

    /// Event vectors of different types stored into void pointers,
    /// accessed through accessEntityEvents
    std::unordered_map<EntityId, std::vector<void*>>    _entityEvents;
    std::vector<std::function<void()>>                  _entityEventDeleters;

    template <typename T_Event>
    std::vector<T_Event>& accessEntityEvents(const EntityId& eId);

    template <typename T_Event>
    void deleteEntityEvents(void* events);
};


template<typename T_Event>
void EventSystem::sendEvent(const EntityId& eId, const T_Event& event)
{
    auto& events = accessEntityEvents<T_Event>(eId);
    events.push_back(event);
}


template<typename T_Event>
std::vector<T_Event>& EventSystem::accessEntityEvents(const EntityId& eId)
{
    auto& ev = _entityEvents[eId];
    auto typeId = EventTypeId::typeId<T_Event>();
    if (ev.size() <= typeId)
        ev.resize((unsigned long long)typeId + 1, nullptr);

    if (ev[typeId] == nullptr) {
        ev[typeId] = new std::vector<T_Event>();

        _entityEventClearers.push_back(std::bind(
            &EventSystem::clearEntityEvents<T_Event>, this, ev[typeId]));
    }

    return *static_cast<std::vector<T_Event>*>(ev[typeId]);
}

template<typename T_Event>
void EventSystem::deleteEntityEvents(void* events)
{
    delete static_cast<std::vector<T_Event>*>(events);
}


#endif //ECSTESTGAME_EVENTSYSTEM_HPP
