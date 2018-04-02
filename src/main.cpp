#include <iostream>

#include "Container.hpp"
#include "System.hpp"


class TestSystem1 : public System<TestSystem1, int, float> {
public:
    void operator()(int& c1, float& c2) {
        ++c1;
        c2+=1.0f;

        printf("TestSystem1: %d, %0.2f\n", c1, c2);
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

    TestSystem1 ts1;
    c.runSystem(ts1);

    return 0;
}
