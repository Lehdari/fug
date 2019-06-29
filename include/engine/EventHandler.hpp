//
// Project: fug
// File: EventHandler.hpp
//
// Copyright (c) 2019 Miika 'Lehdari' Lehtimäki
// You may use, distribute and modify this code under the terms
// of the licence specified in file LICENSE which is distributed
// with this source code package.
//

#ifndef FUG_ENGINE_EVENTHANDLER_HPP
#define FUG_ENGINE_EVENTHANDLER_HPP


#include <vector>
#include <utils/Types.hpp>


#define FUG_EVENT_HANDLER(HANDLER_TYPE, EVENT_TYPE) \
        struct HANDLER_TYPE :\
        public fug::EventHandler<HANDLER_TYPE, EVENT_TYPE> {\
            using EventType = EVENT_TYPE;\
            static void handleEvent(fug::Ecs& ecs, const fug::EntityId& eId, const EVENT_TYPE& event);\
        }


#define FUG_EVENT_LOGIC_HANDLER(HANDLER_TYPE, EVENT_TYPE, LOGIC_TYPE) \
        struct HANDLER_TYPE :\
        public fug::EventLogicHandler<HANDLER_TYPE, EVENT_TYPE, LOGIC_TYPE> {\
            using EventType = EVENT_TYPE;\
            using LogicType = LOGIC_TYPE;\
            static void handleEvent(fug::Ecs& ecs, const fug::EntityId& eId,\
                                    LOGIC_TYPE& logic, const EVENT_TYPE& event);\
        }


namespace fug {

    class Ecs;


    template <typename T_Handler, typename T_Event>
    struct EventHandler {
        static const bool hasLogic = false;
        static void handleEvents(Ecs& ecs, const EntityId& eId, void* events);
    };

    template <typename T_Handler, typename T_Event, typename T_Logic>
    struct EventLogicHandler {
        static const bool hasLogic = true;
        static void handleEvents(Ecs& ecs, const EntityId& eId, void* logic, void* events);
    };


    template<typename T_Handler, typename T_Event>
    void EventHandler<T_Handler, T_Event>::handleEvents(
        Ecs& ecs, const EntityId& eId, void *events)
    {
        auto* events2 = static_cast<std::vector<T_Event>*>(events);
        for (auto& event : *events2)
            T_Handler::handleEvent(ecs, eId, event);
    }


    template<typename T_Handler, typename T_Event, typename T_Logic>
    void EventLogicHandler<T_Handler, T_Event, T_Logic>::handleEvents(
        Ecs& ecs, const EntityId& eId, void *logic, void *events)
    {
        auto* events2 = static_cast<std::vector<T_Event>*>(events);
        auto& logic2 = *static_cast<T_Logic*>(logic);
        for (auto& event : *events2)
            T_Handler::handleEvent(ecs, eId, logic2, event);
    }

} //namespace fug


#endif //FUG_ENGINE_EVENTHANDLER_HPP
