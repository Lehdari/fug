#ifndef FUG_TEST_RESOURCES_HPP
#define FUG_TEST_RESOURCES_HPP


#include "Resource.hpp"


namespace fug {

    struct TestResource1_Init_Default {

    };

    class FUG_RESOURCE(TestResource1) {
        FUG_RESOURCE_INIT_DESTROY_DECL
    };

}


#endif // FUG_TEST_RESOURCES_HPP
