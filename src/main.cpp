#include <iostream>

#include "Container.hpp"


int main(void) {
    Container c;

    c.addComponent(0.0f);
    c.addComponent(0);
    c.addComponent(1);
    c.addComponent(13.2f);
    c.addComponent(1.0);

    return 0;
}
