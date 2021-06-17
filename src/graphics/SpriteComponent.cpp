//
// Project: fug
// File: SpriteComponent.cpp
//
// Copyright (c) 2021 Miika 'Lehdari' Lehtimäki
// You may use, distribute and modify this code under the terms
// of the licence specified in file LICENSE which is distributed
// with this source code package.
//

#include <graphics/SpriteComponent.hpp>


using namespace fug;


SpriteComponent::SpriteComponent(SpriteSheetId sheetId, int spriteId) :
    _dirty          (true),
    _spriteSheetId  (sheetId),
    _spriteId       (spriteId),
    _origin         (0.0f, 0.0f),
    _rotation       (0.0f),
    _scale          (1.0f, 1.0f),
    _positions      {Vec2f(0.0f, 0.0f)},
    _texCoords      {Vec2f(0.0f, 0.0f)}
{
}

void SpriteComponent::setSpriteSheet(SpriteSheetId sheetId)
{
    _spriteSheetId = sheetId;
    _dirty = true;
}

void SpriteComponent::setSprite(int spriteId)
{
    _spriteId = spriteId;
    _dirty = true;
}

void SpriteComponent::setOrigin(const Vec2f& origin)
{
    _origin = origin;
    _dirty = true;
}

void SpriteComponent::setRotation(float rotation)
{
    _rotation = rotation;
    _dirty = true;
}

void SpriteComponent::setScale(const Vec2f& scale)
{
    _scale = scale;
    _dirty = true;
}
