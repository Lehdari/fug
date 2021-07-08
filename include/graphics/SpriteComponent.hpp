//
// Project: fug
// File: SpriteComponent.hpp
//
// Copyright (c) 2021 Miika 'Lehdari' Lehtimäki
// You may use, distribute and modify this code under the terms
// of the licence specified in file LICENSE which is distributed
// with this source code package.
//

#ifndef FUG_GRAPHICS_SPRITECOMPONENT_HPP
#define FUG_GRAPHICS_SPRITECOMPONENT_HPP


#include "SpriteSheet.hpp"
#include <gut_utils/MathUtils.hpp>


namespace fug {

    class SpriteComponent {
    public:
        SpriteComponent(SpriteSheetId sheetId = 0, int spriteId = -1);

        void setSpriteSheet(SpriteSheetId sheetId);
        void setSprite(int spriteId);
        void setOrigin(const Vec2f& origin);
        void setColor(const Vec3f& color);

        SpriteSheetId getSpriteSheet() const;
        int getSprite() const;
        const Vec2f& getOrigin() const;
        const Vec3f& getColor() const;

        friend class SpriteSystem;

    private:
        bool            _dirty;
        SpriteSheetId   _spriteSheetId;
        int             _spriteId;
        Vec2f           _origin;
        Vec3f           _color;
        Vec3f           _positions[4]; // homogeneous vector
        Vec2f           _texCoords[4];
    };

} // namespace fug


#endif //FUG_GRAPHICS_SPRITECOMPONENT_HPP
