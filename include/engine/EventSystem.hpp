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

    EventSystem(const EventSystem&) = delete;
    EventSystem& operator=(const EventSystem&) = delete;
    EventSystem(EventSystem&&) = delete;
    EventSystem& operator=(EventSystem&&) = delete;

    ~EventSystem();

    void operator()(const EntityId& eId, EventComponent& ec);

    /** sendEvent
     * @brief   Send event to an entity
     *
     * @param   eId   Id of the entity the event is sent to
     * @param   event Event to be sent
     */
    template <typename T_Event>
    void sendEvent(const EntityId& eId, const T_Event& event);

    /** broadcastEvent
     * @brief   Broadcast event to all entities
     *
     * @param   event Event to be sent
     */
    template <typename T_Event>
    void broadcastEvent(const T_Event& event);

    /** clear
     *  @brief  Clear all events from EventSystem
     */
    void clear();

private:
    Ecs&    _ecs;

    /// Event vectors of different types stored into void pointers,
    /// accessed through accessEntityEvents
    std::unordered_map<EntityId, std::vector<void*>>    _entityEvents;
    std::vector<std::function<void()>>                  _entityEventClearers;
    std::vector<std::function<void()>>                  _entityEventDeleters;

    /// Event vectors of broadcasted events, accessed through accessBroadcastEvents
    std::vector<void*>                  _broadcastEvents;
    std::vector<std::function<void()>>  _broadcastEventClearers;
    std::vector<std::function<void()>>  _broadcastEventDeleters;

    template <typename T_Event>
    std::vector<T_Event>& accessEntityEvents(const EntityId& eId);

    template <typename T_Event>
    std::vector<T_Event>& accessBroadcastEvents();

    template <typename T_Event>
    void clearEvents(void* events);

    template <typename T_Event>
    void deleteEvents(void* events);
};


template<typename T_Event>
void EventSystem::sendEvent(const EntityId& eId, const T_Event& event)
{
    auto& events = accessEntityEvents<T_Event>(eId);
    events.push_back(event);
}

template<typename T_Event>
void EventSystem::broadcastEvent(const T_Event& event)
{
    auto& events = accessBroadcastEvents<T_Event>();
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
            &EventSystem::clearEvents<T_Event>, this, ev[typeId]));
        _entityEventDeleters.push_back(std::bind(
            &EventSystem::deleteEvents<T_Event>, this, ev[typeId]));
    }

    return *static_cast<std::vector<T_Event>*>(ev[typeId]);
}

template<typename T_Event>
std::vector<T_Event>& EventSystem::accessBroadcastEvents()
{
    auto typeId = EventTypeId::typeId<T_Event>();
    if (_broadcastEvents.size() <= typeId)
        _broadcastEvents.resize((unsigned long long)typeId + 1, nullptr);

    if (_broadcastEvents[typeId] == nullptr) {
        _broadcastEvents[typeId] = new std::vector<T_Event>();

        _broadcastEventClearers.push_back(std::bind(
            &EventSystem::clearEvents<T_Event>,
            this, _broadcastEvents[typeId]));
        _broadcastEventDeleters.push_back(std::bind(
            &EventSystem::deleteEvents<T_Event>,
            this, _broadcastEvents[typeId]));
    }

    return *static_cast<std::vector<T_Event>*>(_broadcastEvents[typeId]);
}

template<typename T_Event>
void EventSystem::clearEvents(void *events)
{
    static_cast<std::vector<T_Event>*>(events)->clear();
}

template<typename T_Event>
void EventSystem::deleteEvents(void* events)
{
    delete static_cast<std::vector<T_Event>*>(events);
}


#endif //ECSTESTGAME_EVENTSYSTEM_HPP
