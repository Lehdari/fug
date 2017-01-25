///  In this file wanted interface implementations and used components are chosen.

#ifndef FUG_IMPLEMENTATION_HPP
#define FUG_IMPLEMENTATION_HPP


#include "Core/Macros.hpp"

#define FUG_IMPLEMENTATION_SCENE            BasicScene
#define FUG_IMPLEMENTATION_EVENT_MANAGER    BasicEventManager
#define FUG_IMPLEMENTATION_RESOURCE_MANAGER BasicResourceManager


namespace fug {

    class FUG_IMPLEMENTATION_SCENE;
    class FUG_IMPLEMENTATION_EVENT_MANAGER;
    class FUG_IMPLEMENTATION_RESOURCE_MANAGER;

    using SceneImplementation           = FUG_IMPLEMENTATION_SCENE;
    using EventManagerImplementation    = FUG_IMPLEMENTATION_EVENT_MANAGER;
    using ResourceManagerImplementation = FUG_IMPLEMENTATION_RESOURCE_MANAGER;

};


#endif // FUG_IMPLEMENTATION_HPP
