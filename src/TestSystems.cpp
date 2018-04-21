//
// Created by Lehdari on 21.4.2018.
//

#include "TestSystems.hpp"
#include <cstdio>   //  TEMP


void TestSystem1::operator()(TestComponent1& c1) {
    ++c1.a;
    ++c1.b;
    ++c1.c;
}

void TestSystem2::operator()(TestComponent1& c1, TestComponent2& c2) {
    ++c1.a;
    //++c1.b;
    ++c1.c;
    //++c2.a;
    ++c2.b;
    //++c2.c;
}

void TestSystem3::operator()(TestComponent1& c1, TestComponent2& c2, TestComponent3& c3) {
    //static uint64_t count = 0;
    //printf("TestSystem3: %llu\n", ++count);
    //if (count == 1000)
    //    printf("benis1\n");
    ++c1.a;
    //if (count == 1000)
    //    printf("benis2\n");
    //++c1.b;
    //++c1.c;
    ++c2.a;
    //if (count == 1000)
    //    printf("benis3\n");
    //++c2.b;
    //++c2.c;
    ++c3.a;
    //if (count == 1000)
    //    printf("benis4\n");
    //++c3.b;
    //++c3.c;
}
