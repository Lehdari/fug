//
// Project: fug
// File: Orientation2DComponent.cpp
//
// Copyright (c) 2021 Miika 'Lehdari' Lehtimäki
// You may use, distribute and modify this code under the terms
// of the licence specified in file LICENSE which is distributed
// with this source code package.
//

#include <graphics/Orientation2DComponent.hpp>


fug::Orientation2DComponent::Orientation2DComponent(const Vec2f& position, float rotation)
{
    float rsin = std::sin(rotation);
    float rcos = std::cos(rotation);
    _orientation <<
        rcos,   -rsin,  position(0),
        rsin,   rcos,   position(1),
        0.0f,   0.0f,   1.0f;
}
