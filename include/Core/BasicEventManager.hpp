#ifndef FUG_BASIC_EVENT_MANAGER_HPP
#define FUG_BASIC_EVENT_MANAGER_HPP


#include "EventManager.hpp"


namespace fug {

    class BasicEventManager : public EventManagerBase<BasicEventManager> {
    };


    #include "BasicEventManager.tcc"

}


#endif // FUG_BASIC_EVENT_MANAGER_HPP
