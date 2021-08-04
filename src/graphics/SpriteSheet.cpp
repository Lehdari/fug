//
// Project: fug
// File: SpriteSheet.cpp
//
// Copyright (c) 2021 Miika 'Lehdari' Lehtimäki
// You may use, distribute and modify this code under the terms
// of the licence specified in file LICENSE which is distributed
// with this source code package.
//

#include <graphics/SpriteSheet.hpp>


using namespace fug;


SpriteSheet::SpriteSheet() :
    _spriteWidth    (0),
    _spriteHeight   (0),
    _nSpritesX      (0),
    _nSpritesY      (0)
{
}

SpriteSheet::SpriteSheet(
    const std::string& fileName,
    int spriteWidth,
    int spriteHeight) :
    _spriteWidth    (spriteWidth),
    _spriteHeight   (spriteHeight)
{
    _texture.loadFromFile(fileName);
    _texture.setFiltering(GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    _nSpritesX = _texture.width() / _spriteWidth;
    _nSpritesY = _texture.height() / _spriteHeight;
}

void SpriteSheet::loadFromFile(
    const std::string& fileName,
    int spriteWidth,
    int spriteHeight)
{
    _texture.loadFromFile(fileName);
    _texture.setFiltering(GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    _spriteWidth = spriteWidth;
    _spriteHeight = spriteHeight;
    _nSpritesX = _texture.width() / _spriteWidth;
    _nSpritesY = _texture.height() / _spriteHeight;
}

void SpriteSheet::getDimensions(int spriteId, int& spriteWidth, int& spriteHeight)
{
    spriteWidth = _spriteWidth;
    spriteHeight = _spriteHeight;
}

void SpriteSheet::getUVCoordinates(int spriteId,
    float& left, float& right, float& top, float& bottom)
{
    int spriteIdX = spriteId % _nSpritesX;
    int spriteIdY = spriteId / _nSpritesX;
    left = (spriteIdX*_spriteWidth) / (float)_texture.width();
    right = ((spriteIdX+1)*_spriteWidth) / (float)_texture.width();
    top = (spriteIdY*_spriteHeight) / (float)_texture.height();
    bottom = ((spriteIdY+1)*_spriteHeight) / (float)_texture.height();
}
