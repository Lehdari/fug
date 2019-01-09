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
    auto& events = _entityEvents[eId];
    // loop event type ids
    for (int64_t etId=0; etId<events.size(); ++etId) {
        if (events[etId] == nullptr || ec._handlers.find(etId) == ec._handlers.end())
            continue;

        ec._handlers[etId](eId, events[etId]);
    }
}
