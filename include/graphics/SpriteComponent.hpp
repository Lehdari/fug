#ifndef FUG_GRAPHICS_SPRITECOMPONENT_HPP
#define FUG_GRAPHICS_SPRITECOMPONENT_HPP


#include <GL/glew.h>
#include <ecs/Ecs.hpp>
#include <glsprite.hh>
#include <vecmat/vec2f.h>
#include <vecmat/vec2i.h>

#include "SpriteSheet.hpp"


namespace fug {

    struct SpriteComponent {
        SpriteComponent() = default;
        SpriteComponent(SpriteSheet* sheet, const vm::vec2i &index, const vm::vec2f &origin) :
            sheet(sheet),
            index(index),
            origin(origin)
        { }
        SpriteSheet* sheet;
        vm::vec2i index;
        vm::vec2f origin;
    };

} // namespace fug


#endif // FUG_GRAPHICS_SPRITECOMPONENT_HPP
