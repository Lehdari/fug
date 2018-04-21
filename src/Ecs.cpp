//
// Created by Lehdari on 2.4.2018.
//

#include "Ecs.hpp"


uint64_t Ecs::typeIdCounter = 0;


Ecs::Ecs()
{
}

Ecs::~Ecs()
{
    for (auto& cd : _componentDeleters)
        cd();
}