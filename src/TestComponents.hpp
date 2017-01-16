#ifndef FUG_TEST_COMPONENTS_HPP
#define FUG_TEST_COMPONENTS_HPP


#include "Component.hpp"


namespace fug {


    class TestComponent1 : public Component {
    public:
        int a;
        int b;
    };

    class TestComponent2 : public Component {
    public:
        float   a;
        float   b;
    };

    class TestComponent3 : public Component {
    public:
        double  a;
        double  b;
    };


}


#endif // FUG_TEST_COMPONENTS_HPP
