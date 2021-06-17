//
// Project: fug
// File: OrientationComponent.hpp
//
// Copyright (c) 2021 Miika 'Lehdari' Lehtimäki
// You may use, distribute and modify this code under the terms
// of the licence specified in file LICENSE which is distributed
// with this source code package.
//

#ifndef FUG_GRAPHICS_ORIENTATION2DCOMPONENT_HPP
#define FUG_GRAPHICS_ORIENTATION2DCOMPONENT_HPP


#include <gut_utils/MathTypes.hpp>


namespace fug {

    struct Orientation2DComponent {
        Mat3f   _orientation;

        Orientation2DComponent(const Vec2f& position = Vec2f(0.0f, 0.0f), float rotation = 0.0f);
    };

} // namespace fug


#endif //FUG_GRAPHICS_ORIENTATION2DCOMPONENT_HPP
