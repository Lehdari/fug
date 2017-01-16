///  In this file wanted interface implementations and used components are chosen.

#ifndef FUG_IMPLEMENTATION_HPP
#define FUG_IMPLEMENTATION_HPP


#include "Macros.hpp"


#ifdef FUG_UNIT_TEST
    /// Implementation and components for unit tests
    #if FUG_UNIT_TEST == 1

            #define FUG_IMPLEMENTATION_SCENE    BasicScene
            #define FUG_COMPONENTS\
                    FUG_COMPONENT   (TestComponent1)\
                    FUG_COMPONENT   (TestComponent2)\
                    FUG_LCOMPONENT  (TestComponent3)

    #endif

#else  //  FUG_UNIT_TEST
    /// Implementation and components for library build

    #define FUG_IMPLEMENTATION_SCENE    BasicScene
    #define FUG_COMPONENTS\
            FUG_COMPONENT   (TestComponent1)\
            FUG_COMPONENT   (TestComponent2)\
            FUG_LCOMPONENT  (TestComponent3)


#endif  //  FUG_UNIT_TEST


namespace fug {

    template <typename... T_SceneComponents>
    class FUG_IMPLEMENTATION_SCENE;

    #define FUG_COMPONENT(x) class x;
    #define FUG_LCOMPONENT(x) class x;
        FUG_COMPONENTS

    #define FUG_COMPONENT(x) x,
    #define FUG_LCOMPONENT(x) x
    using SceneImplementation   = FUG_IMPLEMENTATION_SCENE<FUG_COMPONENTS>;
    #undef FUG_COMPONENT

};


#endif // FUG_IMPLEMENTATION_HPP
