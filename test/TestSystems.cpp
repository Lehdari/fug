//
// Created by Lehdari on 21.4.2018.
//

#include "TestSystems.hpp"
#include <cstdio>   //  TEMP


void TestSystem1::operator()(const EntityId& eId, TestComponent1& c1) {
    //printf("eId: %llu\n", eId);
    ++c1.a;
    ++c1.b;
    ++c1.c;
}

void TestSystem2::operator()(const EntityId& eId, TestComponent1& c1, TestComponent2& c2) {
    ++c1.a;
    //++c1.b;
    ++c1.c;
    //++c2.a;
    ++c2.b;
    //++c2.c;
}

void TestSystem3::operator()(const EntityId& eId, TestComponent1& c1, TestComponent2& c2, TestComponent3& c3) {
    ++c1.a;
    //++c1.b;
    //++c1.c;
    ++c2.a;
    //++c2.b;
    //++c2.c;
    ++c3.a;
    //++c3.b;
    //++c3.c;
}