//
// Created by Lehdari on 9.1.2019.
//

#ifndef ECSTESTGAME_EVENTHANDLER_HPP
#define ECSTESTGAME_EVENTHANDLER_HPP


#include <vector>
#include <Types.hpp>


class Ecs;


#define EVENT_HANDLER(HANDLER_TYPE, EVENT_TYPE) \
        struct HANDLER_TYPE :\
        public EventHandler<HANDLER_TYPE, EVENT_TYPE> {\
            using EventType = EVENT_TYPE;\
            static void handleEvent(Ecs& ecs, const EntityId& eId, const EVENT_TYPE& event);\
        }


template <typename T_Handler, typename T_Event>
struct EventHandler {
    static void handleEvents(Ecs& ecs, const EntityId& eId, void* events) {
        auto* events2 = static_cast<std::vector<T_Event>*>(events);
        for (auto& event : *events2)
            T_Handler::handleEvent(ecs, eId, event);
    }
};


#endif //ECSTESTGAME_EVENTHANDLER_HPP
