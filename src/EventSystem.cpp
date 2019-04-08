//
// Created by Lehdari on 8.1.2019.
//

#include "EventSystem.hpp"
#include "LogicComponent.hpp"


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

    LogicComponent* lc = nullptr;
    if (!ec._logicHandlers.empty())
        lc = _ecs.getComponent<LogicComponent>(eId);

    // handle entity-specific events
    for (int64_t etId=0; etId<eEvents.size(); ++etId) {
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
    for (int64_t etId=0; etId<_broadcastEvents.size(); ++etId) {
        if (_broadcastEvents[etId] == nullptr ||
            ec._handlers.find(etId) == ec._handlers.end())
            continue;

        if (ec._handlers.find(etId) != ec._handlers.end())
            ec._handlers[etId](_ecs, eId, _broadcastEvents[etId]);

        if (lc == nullptr)
            continue;

        if (ec._logicHandlers.find(etId) != ec._logicHandlers.end())
            ec._logicHandlers[etId](_ecs, eId, lc->_logic, _broadcastEvents[etId]);
    }
}

void EventSystem::clear()
{
    for (auto& ec : _entityEventClearers)
        ec();
    for (auto& bc : _broadcastEventClearers)
        bc();
}
