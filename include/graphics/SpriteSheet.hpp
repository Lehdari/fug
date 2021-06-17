//
// Project: fug
// File: SpriteSheet.hpp
//
// Copyright (c) 2021 Miika 'Lehdari' Lehtimäki
// You may use, distribute and modify this code under the terms
// of the licence specified in file LICENSE which is distributed
// with this source code package.
//

#ifndef FUG_GRAPHICS_SPRITESHEET_HPP
#define FUG_GRAPHICS_SPRITESHEET_HPP


#include <gut_opengl/Texture.hpp>
#include <vector>


namespace fug {

    class SpriteSheet {
    public:
        SpriteSheet();

        SpriteSheet(
            const std::string& fileName,
            int spriteWidth,
            int spriteHeight);

        void loadFromFile(
            const std::string& fileName,
            int spriteWidth,
            int spriteHeight);

        void getDimensions(
            int spriteId,
            int& spriteWidth,
            int& spriteHeight);

        void getUVCoordinates(
            int spriteId,
            float& left,
            float& right,
            float& top,
            float& bottom);

        friend class SpriteSingleton;

    private:
        gut::Texture    _texture;
        int             _spriteWidth;
        int             _spriteHeight;
        int             _nSpritesX;
        int             _nSpritesY;
    };


    using SpriteSheetId = std::vector<SpriteSheet>::size_type;

} // namespace fug


#endif //FUG_GRAPHICS_SPRITESHEET_HPP
