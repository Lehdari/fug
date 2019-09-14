//
// Project: fug
// File: Ecs.cpp
//
// Copyright (c) 2019 Miika 'Lehdari' Lehtimäki
// You may use, distribute and modify this code under the terms
// of the licence specified in file LICENSE which is distributed
// with this source code package.
//

#include "Ecs.hpp"


using namespace fug;


Ecs::Ecs()
{
}

Ecs::~Ecs()
{
    for (auto& cd : _componentDeleters)
        cd();

    for (auto& sd : _singletonDeleters)
        sd();
}