#ifndef FUG_TEXTURE_HPP
#define FUG_TEXTURE_HPP

#include "Core/Resource.hpp"
#include "Core/MathTypes.hpp"

#include <GL/glew.h>

namespace fug {
    class FUG_RESOURCE(Texture) {
    public:
        FUG_RESOURCE_INIT_DESTROY_DECL
        Texture(void);
        const Vector2Glf& getSize() const;
        void bind(GLenum target) const;
    private:
        GLuint textureId_;
        
        Vector2Glf _textureSize;
    };
}

#endif //FUG_TEXTURE_HPP
