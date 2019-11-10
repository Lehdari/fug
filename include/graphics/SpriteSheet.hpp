#ifndef FUG_GRAPHICS_SPRITESHEET_HPP
#define FUG_GRAPHICS_SPRITESHEET_HPP


#include <GL/gl3w.h>
#include <ecs/Ecs.hpp>
#include <glsprite.hh>
#include <stb_image.h>
#include <string>
#include <cassert>


namespace fug {

    // TODO: This should be a resource
    struct SpriteSheet {
        SpriteSheet() = default;
        SpriteSheet(const std::string &texturePath,
                    int32_t textureW, int32_t textureH,
                    uint32_t cellW, uint32_t cellH, float margin);
        ~SpriteSheet();

        SpriteSheet(const SpriteSheet&) = delete;
        const SpriteSheet& operator=(const SpriteSheet&) = delete;

        void load(const std::string &texturePath,
                  int32_t textureW, int32_t textureH,
                  uint32_t cellW, uint32_t cellH, float margin);

        GLuint textureID = 0;
        glsprite_sheet sheet = {};
        glsprite_grid grid = {};
    };

} // namespace fug


#endif // FUG_GRAPHICS_SPRITESHEET_HPP
