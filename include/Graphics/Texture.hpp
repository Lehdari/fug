#ifndef FUG_TEXTURE_HPP
#define FUG_TEXTURE_HPP

#include "Core/Resource.hpp"

#include <GL/glew.h>

namespace fug {
    class FUG_RESOURCE(Texture) {
    public:
        FUG_RESOURCE_INIT_DESTROY_DECL
        Texture(void);
        void bind(GLenum target) const;
    private:
        GLuint textureId_;
    };
}

#endif //FUG_TEXTURE_HPP
