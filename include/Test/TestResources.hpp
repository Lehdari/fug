#ifndef FUG_TEST_RESOURCES_HPP
#define FUG_TEST_RESOURCES_HPP


#include "Core/Resource.hpp"


namespace fug {

    class FUG_RESOURCE(TestResource1) {
    public:
        FUG_RESOURCE_INIT_DESTROY_DECL

        int a;
    };

    class FUG_RESOURCE(TestResource2) {
    public:
        FUG_RESOURCE_INIT_DESTROY_DECL

        int a;
    };

}


#endif // FUG_TEST_RESOURCES_HPP
