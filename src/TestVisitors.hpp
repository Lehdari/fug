#ifndef FUG_TEST_VISITORS_HPP
#define FUG_TEST_VISITORS_HPP


#include "Visitor.hpp"
#include "TestComponents.hpp"


namespace fug {


    class TestVisitor1 : public Visitor<TestVisitor1, TestComponent1> {
    public:
        void operator()(TestComponent1& component);
    };


}


#endif // FUG_TEST_VISITORS_HPP
