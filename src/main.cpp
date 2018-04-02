#include <iostream>

#include "Ecs.hpp"
#include "System.hpp"


TECS_SYSTEM(TestSystem1, int, float) {
    void operator()(int& c1, float& c2) {
        ++c1;
        c2+=1.0f;

        printf("TestSystem1: %d, %0.2f\n", c1, c2);
    }
};

TECS_SYSTEM(TestSystem2, int, char) {
    void operator()(int& c1, char& c2) {
        ++c1;
        ++c2;

        printf("TestSystem2: %d, %c\n", c1, c2);
    }
};

TECS_SYSTEM(TestSystem3, long long unsigned, char) {
    void operator()(long long unsigned& c1, char& c2) {
        ++c1;
        ++c2;

        printf("TestSystem3: %llu, %c\n", c1, c2);
    }
};


int main(void) {
    Ecs ecs;

    ecs.addComponent(0.0f);
    ecs.addComponent(0);

    ecs.addEntity();
    ecs.addComponent(1llu);
    ecs.addComponent(1);
    ecs.addComponent(1.0);

    ecs.addEntity();
    ecs.addComponent('C');
    ecs.addComponent(2);
    ecs.addComponent(2.0f);

    ecs.addEntity();
    ecs.addComponent('D');
    ecs.addComponent(3.0);
    ecs.addComponent(3);
    ecs.addComponent(3llu);

    ecs.addEntity();
    ecs.addComponent('E');
    ecs.addComponent(4.0f);
    ecs.addComponent(4llu);


    TestSystem1 ts1;
    ecs.runSystem(ts1);

    TestSystem2 ts2;
    ecs.runSystem(ts2);

    TestSystem3 ts3;
    ecs.runSystem(ts3);


    return 0;
}
