//
// Created by Lehdari on 8.1.2019.
//

#include "EventSystem.hpp"


EventSystem::EventSystem(Ecs& ecs) :
    _ecs    (ecs)
{
}

EventSystem::~EventSystem()
{
    for (auto& ed : _entityEventDeleters)
        ed();
}

void EventSystem::operator()(const EntityId& eId, EventComponent& ec)
{
    auto& eEvents = _entityEvents[eId]; // entity-specific events

    // handle entity-specific events
    for (int64_t etId=0; etId<eEvents.size(); ++etId) {
        // skip event type if no such events has been sent
        // or if no handler for the type is found
        if (eEvents[etId] == nullptr || ec._handlers.find(etId) == ec._handlers.end())
            continue;

        ec._handlers[etId](_ecs, eId, eEvents[etId]);
    }

    // handle broadcasted events
    for (int64_t etId=0; etId<_broadcastEvents.size(); ++etId) {
        if (_broadcastEvents[etId] == nullptr ||
            ec._handlers.find(etId) == ec._handlers.end())
            continue;

        ec._handlers[etId](_ecs, eId, _broadcastEvents[etId]);
    }
}

void EventSystem::clear()
{
    for (auto& ec : _entityEventClearers)
        ec();
    for (auto& bc : _broadcastEventClearers)
        bc();
}
