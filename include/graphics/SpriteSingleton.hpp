//
// Project: fug
// File: SpriteSingleton.hpp
//
// Copyright (c) 2021 Miika 'Lehdari' Lehtimäki
// You may use, distribute and modify this code under the terms
// of the licence specified in file LICENSE which is distributed
// with this source code package.
//

#ifndef FUG_GRAPHICS_SPRITESINGLETON_HPP
#define FUG_GRAPHICS_SPRITESINGLETON_HPP


#include "SpriteSheet.hpp"

#include <gut_utils/TypeUtils.hpp>
#include <gut_opengl/Shader.hpp>


namespace fug {

    class SpriteSingleton {
    public:
        SpriteSingleton();

        SpriteSingleton(const SpriteSingleton&) = delete;
        SpriteSingleton(SpriteSingleton&&) = delete;
        SpriteSingleton& operator=(const SpriteSingleton&) = delete;
        SpriteSingleton& operator=(SpriteSingleton&&) = delete;

        ~SpriteSingleton();

        void init();

        SpriteSheetId addSpriteSheetFromFile(
            const std::string& fileName,
            int spriteWidth,
            int spriteHeight);

        void setWindowSize(int windowWidth, int windowHeight);

        void render(const Mat3f& viewport = Mat3f::Identity());

        friend class SpriteSystem;

    private:
        std::vector<SpriteSheet>    _spriteSheets;
        gut::Shader                 _shader;

        int                         _windowWidth;
        int                         _windowHeight;

        GLuint                      _vertexArrayObjectId;
        GLuint                      _positionBufferId;
        GLuint                      _texCoordBufferId;
        GLuint                      _colorBufferId;

        Vector<Vector<Vec2f>>       _spriteVertexPositions;
        Vector<Vector<Vec2f>>       _spriteVertexTexCoords;
        Vector<Vector<Vec3f>>       _spriteVertexColors;
    };

} // namespace fug


#endif //FUG_GRAPHICS_SPRITESINGLETON_HPP
