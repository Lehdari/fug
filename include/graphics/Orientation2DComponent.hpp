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

    class Orientation2DComponent {
    public:
        Orientation2DComponent(
            const Vec2f& position = Vec2f(0.0f, 0.0f),
            float rotation = 0.0f,
            float scale = 1.0f);

        void setPosition(const Vec2f& position);
        void setRotation(float rotation);
        void setScale(float scale);

        void translate(const Vec2f& translation);
        void rotate(float rotation);
        void scale(float scale);

        const Vec2f& getPosition() const;
        float getRotation() const;
        float getScale() const;
        const Mat3f& getOrientation();

    private:
        Vec2f   _position;
        float   _rotation;
        float   _rotSin;
        float   _rotCos;
        float   _scale;
        Mat3f   _orientation;

        void updateOrientation();
    };

} // namespace fug


#endif //FUG_GRAPHICS_ORIENTATION2DCOMPONENT_HPP
