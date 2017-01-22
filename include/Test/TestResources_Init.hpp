#ifndef FUG_TEST_RESOURCES_INIT_HPP
#define FUG_TEST_RESOURCES_INIT_HPP


#include "Test/TestResources.hpp"


namespace fug {

    struct TestResource1_Init_Default {
        int a;
        int b;
    };

    struct TestResource2_Init_TestResource1 {
        float a;
        float b;
    };

    struct TestResource3_Init_TestResource2 {
        double a;
        double b;
    };


    #include "TestResources_Init.tcc"

}


#endif // FUG_TEST_RESOURCES_INIT_HPP
