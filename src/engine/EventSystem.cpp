//
// Created by Lehdari on 8.1.2019.
//

#include <engine/EventSystem.hpp>
#include <engine/LogicComponent.hpp>


EventSystem::EventSystem(Ecs& ecs) :
    _ecs                        (ecs),
    _dirty                      (false),
    _activeEntityEvents         (&_entityEvents1),
    _inactiveEntityEvents       (&_entityEvents2),
    _activeBroadcastEvents      (&_broadcastEvents1),
    _inactiveBroadcastEvents    (&_broadcastEvents2)
{
}

EventSystem::~EventSystem()
{
    for (auto& ed : _entityEventDeleters)
        ed();
    for (auto& bd : _broadcastEventDeleters)
        bd();
}

void EventSystem::operator()(const EntityId& eId, EventComponent& ec)
{
    auto& eEvents = (*_inactiveEntityEvents)[eId]; // entity-specific events
    auto& bEvents = *_inactiveBroadcastEvents; // broadcasted events

    LogicComponent *lc = nullptr;
    if (!ec._logicHandlers.empty())
        lc = _ecs.getComponent<LogicComponent>(eId);

    // handle entity-specific events
    for (int64_t etId = 0; etId < eEvents.size(); ++etId) {
        // skip event type if no such events has been sent
        // or if no handler for the type is found
        if (eEvents[etId] == nullptr)
            continue;

        if (ec._handlers.find(etId) != ec._handlers.end())
            ec._handlers[etId](_ecs, eId, eEvents[etId]);

        if (lc == nullptr)
            continue;

        if (ec._logicHandlers.find(etId) != ec._logicHandlers.end())
            ec._logicHandlers[etId](_ecs, eId, lc->_logic, eEvents[etId]);
    }

    // handle broadcasted events
    for (int64_t etId = 0; etId < bEvents.size(); ++etId) {
        if (bEvents[etId] == nullptr)
            continue;

        if (ec._handlers.find(etId) != ec._handlers.end())
            ec._handlers[etId](_ecs, eId, bEvents[etId]);

        if (lc == nullptr)
            continue;

        if (ec._logicHandlers.find(etId) != ec._logicHandlers.end())
            ec._logicHandlers[etId](_ecs, eId, lc->_logic, bEvents[etId]);
    }
}

bool EventSystem::swap()
{
    auto& eEvents = *_inactiveEntityEvents;
    auto& bEvents = *_inactiveBroadcastEvents;

    //  Clear inactive entity events
    for (auto& ev : eEvents) {
        for (int64_t etId = 0; etId < ev.second.size(); ++etId) {
            auto ec = _eventClearers[etId];
            if (ec && ev.second[etId])
                (this->*ec)(ev.second[etId]);
        }
    }

    //  Clear inactive broadcasted events
    for (int64_t etId = 0; etId < bEvents.size(); ++etId) {
        auto ec = _eventClearers[etId];
        if (ec && bEvents[etId])
            (this->*ec)(bEvents[etId]);
    }

    //  Swap the buffers
    std::swap(_activeEntityEvents, _inactiveEntityEvents);
    std::swap(_activeBroadcastEvents, _inactiveBroadcastEvents);

    bool dirty = _dirty;
    _dirty = false;
    return dirty;
}
