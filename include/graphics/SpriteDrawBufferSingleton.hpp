#ifndef FUG_GRAPHICS_SPRITEDRAWBUFFERSINGLETON_HPP
#define FUG_GRAPHICS_SPRITEDRAWBUFFERSINGLETON_HPP

#include <GL/glew.h>
#include <ecs/Ecs.hpp>
#include <glsprite.hh>

#include <map>


namespace fug {

    struct SpriteDrawBufferSingleton {
        ~SpriteDrawBufferSingleton() {
            for (auto& [id, buffer] : buffers) {
                glsprite_draw_buffer_destroy(&buffer);
            }
        }
        std::map<GLuint, glsprite_draw_buffer> buffers;
    };

} // namespace fug


#endif // FUG_GRAPHICS_SPRITEDRAWBUFFERSINGLETON_HPP
