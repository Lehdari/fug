#ifndef FUG_EVENT_MANAGER_HPP
#define FUG_EVENT_MANAGER_HPP


#include "Implementation.hpp"


namespace fug {

    template <typename T_EventManagerImplementation>
    class EventManagerBase {
    };


    #include "EventManager.tcc"


    using EventManager = EventManagerBase<EventManagerImplementation>;

}

/// include implementation headers here
#include "BasicEventManager.hpp"


#endif // FUG_EVENT_MANAGER_HPP
