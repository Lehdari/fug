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


using namespace fug;


Orientation2DComponent::Orientation2DComponent(
    const Vec2f& position,
    float rotation,
    float scale
    ) :
    _position   (position),
    _rotation   (rotation),
    _rotSin     (std::sin(_rotation)),
    _rotCos     (std::cos(_rotation)),
    _scale      (1.0f)
{
    updateOrientation();
}

void Orientation2DComponent::setPosition(const Vec2f& position)
{
    _position = position;
    updateOrientation();
}

void Orientation2DComponent::setRotation(float rotation)
{
    _rotation = rotation;
    _rotSin = std::sin(_rotation);
    _rotCos = std::cos(_rotation);
    updateOrientation();
}

void Orientation2DComponent::setScale(float scale)
{
    _scale = scale;
    updateOrientation();
}

void Orientation2DComponent::translate(const Vec2f& translation)
{
    _position += translation;
    updateOrientation();
}

void Orientation2DComponent::rotate(float rotation)
{
    _rotation += rotation;
    updateOrientation();
}

void Orientation2DComponent::scale(float scale)
{
    _scale *= scale;
    updateOrientation();
}

const Vec2f& Orientation2DComponent::getPosition() const
{
    return _position;
}

float Orientation2DComponent::getRotation() const
{
    return _rotation;
}

float Orientation2DComponent::getScale() const
{
    return _scale;
}

const Mat3f& Orientation2DComponent::getOrientation()
{
    return _orientation;
}

void Orientation2DComponent::updateOrientation()
{
    _orientation <<
        _rotCos*_scale, -_rotSin*_scale,    _position(0),
        _rotSin*_scale, _rotCos*_scale,     _position(1),
        0.0f,           0.0f,               1.0f;
}
