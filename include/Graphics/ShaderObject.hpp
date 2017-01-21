#ifndef FUG_SHADER_OBJECT_HPP
#define FUG_SHADER_OBJECT_HPP

#include "Core/Resource.hpp"

#include "glLoadGen/gl_core_3_3.h"

namespace fug {
    class FUG_RESOURCE(ShaderObject) {
    public:
        FUG_RESOURCE_INIT_DESTROY_DECL
        ShaderObject(void);
        GLuint getId(void) const;
    private:
        GLuint objectId_;
    };
}

#endif // FUG_SHADER_OBJECT_HPP
