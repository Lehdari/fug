//
// Created by Lehdari on 21.4.2018.
//

#ifndef TEMPLATEECS_TESTSYSTEMS_HPP
#define TEMPLATEECS_TESTSYSTEMS_HPP


#include "System.hpp"
#include "TestComponents.hpp"


TECS_SYSTEM(TestSystem1, TestComponent1) {
    void operator()(TestComponent1& c1);
};

TECS_SYSTEM(TestSystem2, TestComponent1, TestComponent2) {
    void operator()(TestComponent1& c1, TestComponent2& c2);
};

TECS_SYSTEM(TestSystem3, TestComponent1, TestComponent2, TestComponent3) {
    void operator()(TestComponent1& c1, TestComponent2& c2, TestComponent3& c3);
};


#endif //TEMPLATEECS_TESTSYSTEMS_HPP
