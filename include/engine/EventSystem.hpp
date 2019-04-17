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
     *  @brief  Swap the buffers of EventSystem
     *
     *  @return Boolean whether there were events to process
     */
    bool swap();

private:
    Ecs&    _ecs;
    bool    _dirty; //  flag whether there is more events to be handled

    /// Event vectors of different types stored into void pointers,
    /// accessed through accessEntityEvents
    using EntityEvents = std::unordered_map<EntityId, std::vector<void*>>;
    EntityEvents                        _entityEvents1;
    EntityEvents                        _entityEvents2;
    EntityEvents*                       _activeEntityEvents;    //  active: added to
    EntityEvents*                       _inactiveEntityEvents;  //  inactive: handled from
    std::vector<std::function<void()>>  _entityEventDeleters;

    /// Event vectors of broadcasted events, accessed through accessBroadcastEvents
    std::vector<void*>                  _broadcastEvents1;
    std::vector<void*>                  _broadcastEvents2;
    std::vector<void*>*                 _activeBroadcastEvents;
    std::vector<void*>*                 _inactiveBroadcastEvents;
    std::vector<std::function<void()>>  _broadcastEventDeleters;

    std::vector<void(EventSystem::*)(void* events)> _eventClearers;

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
    _dirty = true;
}

template<typename T_Event>
void EventSystem::broadcastEvent(const T_Event& event)
{
    auto& events = accessBroadcastEvents<T_Event>();
    events.push_back(event);
    _dirty = true;
}

template<typename T_Event>
std::vector<T_Event>& EventSystem::accessEntityEvents(const EntityId& eId)
{
    auto& aev = (*_activeEntityEvents)[eId];
    auto& iev = (*_inactiveEntityEvents)[eId];

    auto typeId = EventTypeId::typeId<T_Event>();
    if (aev.size() <= typeId) {
        aev.resize((unsigned long long)typeId+1, nullptr);
        iev.resize((unsigned long long)typeId+1, nullptr);
    }

    if (aev[typeId] == nullptr) {
        aev[typeId] = new std::vector<T_Event>();

        _entityEventDeleters.push_back(std::bind(
            &EventSystem::deleteEvents<T_Event>, this, aev[typeId]));
    }

    if (_eventClearers.size() <= typeId)
        _eventClearers.resize((unsigned long long)typeId+1, nullptr);

    if (_eventClearers[typeId] == nullptr)
        _eventClearers[typeId] = &EventSystem::clearEvents<T_Event>;

    return *static_cast<std::vector<T_Event>*>(aev[typeId]);
}

template<typename T_Event>
std::vector<T_Event>& EventSystem::accessBroadcastEvents()
{
    auto& abv = *_activeBroadcastEvents;
    auto& ibv = *_inactiveBroadcastEvents;

    auto typeId = EventTypeId::typeId<T_Event>();
    if (abv.size() <= typeId) {
        abv.resize((unsigned long long)typeId+1, nullptr);
        ibv.resize((unsigned long long)typeId+1, nullptr);
    }

    if (abv[typeId] == nullptr) {
        abv[typeId] = new std::vector<T_Event>();

        _broadcastEventDeleters.push_back(std::bind(
            &EventSystem::deleteEvents<T_Event>, this, abv[typeId]));
    }

    if (_eventClearers.size() <= typeId)
        _eventClearers.resize((unsigned long long)typeId+1, nullptr);

    if (_eventClearers[typeId] == nullptr)
        _eventClearers[typeId] = &EventSystem::clearEvents<T_Event>;

    return *static_cast<std::vector<T_Event>*>(abv[typeId]);
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
