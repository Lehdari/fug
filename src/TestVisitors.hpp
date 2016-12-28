#ifndef FUG_TEST_VISITORS_HPP
#define FUG_TEST_VISITORS_HPP


#include "Visitor.hpp"
#include "TestComponents.hpp"


namespace fug {


    class TestVisitor1 : public Visitor<TestVisitor1, TestComponent1> {
    public:
        void operator()(TestComponent1& component);
    };

    class TestVisitor2 : public Visitor<TestVisitor1, TestComponent1, TestComponent2> {
    public:
        void operator()(TestComponent1& component1, TestComponent2& component2);
    };


}


#endif // FUG_TEST_VISITORS_HPP
