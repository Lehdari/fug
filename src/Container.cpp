#include "Container.hpp"


uint64_t Container::typeIdCounter = 0;


Container::~Container() {
    for (auto& cd : _componentDeleters)
        cd();
}
