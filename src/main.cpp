#include <iostream>

#include "Container.hpp"
#include "System.hpp"


TECS_SYSTEM(TestSystem1, int, float) {
public:
    void operator()(int& c1, float& c2) {
        ++c1;
        c2+=1.0f;

        printf("TestSystem1: %d, %0.2f\n", c1, c2);
    }
};

TECS_SYSTEM(TestSystem2, int, char) {
public:
    void operator()(int& c1, char& c2) {
        ++c1;
        ++c2;

        printf("TestSystem2: %d, %c\n", c1, c2);
    }
};

TECS_SYSTEM(TestSystem3, long long unsigned, char) {
public:
    void operator()(long long unsigned& c1, char& c2) {
        ++c1;
        ++c2;

        printf("TestSystem3: %llu, %c\n", c1, c2);
    }
};


int main(void) {
    Container c;

    c.addComponent(0.0f);
    c.addComponent(0);

    c.addEntity();
    c.addComponent(1llu);
    c.addComponent(1);
    c.addComponent(1.0);

    c.addEntity();
    c.addComponent('C');
    c.addComponent(2);
    c.addComponent(2.0f);

    c.addEntity();
    c.addComponent('D');
    c.addComponent(3.0);
    c.addComponent(3);
    c.addComponent(3llu);

    c.addEntity();
    c.addComponent('E');
    c.addComponent(4.0f);
    c.addComponent(4llu);


    TestSystem1 ts1;
    c.runSystem(ts1);

    TestSystem2 ts2;
    c.runSystem(ts2);

    TestSystem3 ts3;
    c.runSystem(ts3);


    return 0;
}
