#include <iostream>

#include "Tests.hpp"

#include "Ecs.hpp"
#include "TestSystems.hpp"


int main(void) {

    test0();
    test1();
    test2();
    test3();
/*
    Ecs ecs;
    ecs.addComponent(3, TestComponent1());
    ecs.addComponent(1, TestComponent1());
    ecs.addComponent(2, TestComponent1());
    ecs.addComponent(0, TestComponent1());


    TestSystem1 sys;
    ecs.runSystem(sys);
    printf("\n");
    ecs.removeComponent<TestComponent1>(2);
    ecs.runSystem(sys);
    printf("\n");
*/
    return 0;
}
