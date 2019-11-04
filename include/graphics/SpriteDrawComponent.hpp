#ifndef FUG_GRAPHICS_SPRITEDRAWCOMPONENT_HPP
#define FUG_GRAPHICS_SPRITEDRAWCOMPONENT_HPP


#include <GL/gl3w.h>
#include <ecs/Ecs.hpp>
#include <glsprite.hh>
#include <vecmat/vec2f.h>
#include <vecmat/vec2i.h>

#include "SpriteSheet.hpp"


namespace fug {

    struct SpriteDrawComponent {
        SpriteDrawComponent() = default;
        SpriteDrawComponent(SpriteSheet* sheet, const vm::vec2i &index, const vm::vec2f &origin) :
            sheet(sheet),
            index(index),
            origin(origin)
        { }
        SpriteSheet* sheet;
        vm::vec2i index;
        vm::vec2f origin;
    };

} // namespace fug


#endif // FUG_GRAPHICS_SPRITEDRAWCOMPONENT_HPP
