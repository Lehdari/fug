#include <iostream>

#include "Container.hpp"


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
    c.addComponent(2.0f);

    c.addEntity();
    c.addComponent('D');
    c.addComponent(4.0);
    c.addComponent(4);
    c.addComponent(4llu);

    return 0;
}
