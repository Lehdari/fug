///  In this file wanted interface implementations and used components are chosen.

#ifndef FUG_IMPLEMENTATION_HPP
#define FUG_IMPLEMENTATION_HPP


#include "Core/Macros.hpp"


#if FUG_UNIT_TEST != 0
    /// Implementation and components for unit tests
    //#if FUG_UNIT_TEST == 1

            #define FUG_IMPLEMENTATION_SCENE            BasicScene
            #define FUG_IMPLEMENTATION_EVENT_MANAGER    BasicEventManager
            #define FUG_IMPLEMENTATION_RESOURCE_MANAGER BasicResourceManager

            #define FUG_COMPONENTS\
                    FUG_COMPONENT   (TestComponent1)\
                    FUG_COMPONENT   (TestComponent2)\
                    FUG_LCOMPONENT  (TestComponent3)

    //#endif

#else  //  FUG_UNIT_TEST
    /// Implementation and components for library build

    #define FUG_IMPLEMENTATION_SCENE            BasicScene
    #define FUG_IMPLEMENTATION_EVENT_MANAGER    BasicEventManager
    #define FUG_IMPLEMENTATION_RESOURCE_MANAGER BasicResourceManager

    #define FUG_COMPONENTS\
            FUG_COMPONENT   (CharacterInfoComponent)\
            FUG_COMPONENT   (PlayerComponent)\
            FUG_LCOMPONENT  (CharacterStateComponent)

#endif  //  FUG_UNIT_TEST


namespace fug {

    #define FUG_COMPONENT(x) class x;
    #define FUG_LCOMPONENT(x) class x;
    FUG_COMPONENTS
    #undef FUG_COMPONENT
    #undef FUG_LCOMPONENT

    template <typename... T_SceneComponents>
    class FUG_IMPLEMENTATION_SCENE;
    class FUG_IMPLEMENTATION_EVENT_MANAGER;
    class FUG_IMPLEMENTATION_RESOURCE_MANAGER;

    #define FUG_COMPONENT(x) x,
    #define FUG_LCOMPONENT(x) x
    using SceneImplementation           = FUG_IMPLEMENTATION_SCENE<FUG_COMPONENTS>;
    #undef FUG_COMPONENT
    #undef FUG_LCOMPONENT

    using EventManagerImplementation    = FUG_IMPLEMENTATION_EVENT_MANAGER;
    using ResourceManagerImplementation = FUG_IMPLEMENTATION_RESOURCE_MANAGER;

};


#endif // FUG_IMPLEMENTATION_HPP
