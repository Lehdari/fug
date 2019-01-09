//
// Created by Lehdari on 9.1.2019.
//

#ifndef ECSTESTGAME_EVENTHANDLER_HPP
#define ECSTESTGAME_EVENTHANDLER_HPP


#include <vector>
#include <Types.hpp>


#define EVENT_HANDLER(HANDLER_NAME, EVENT_TYPE) \
        struct HANDLER_NAME :\
        public EventHandler<HANDLER_NAME, EVENT_TYPE> {\
            using EventType = EVENT_TYPE;\
            static void handleEvent(const EntityId& eId, const EVENT_TYPE& event);\
        }


template <typename T_Handler, typename T_Event>
struct EventHandler {
    static void handleEvents(const EntityId& eId, void* events) {
        auto* events2 = static_cast<std::vector<T_Event>*>(events);
        for (auto& event : *events2)
            T_Handler::handleEvent(eId, event);
    }
};


#endif //ECSTESTGAME_EVENTHANDLER_HPP
