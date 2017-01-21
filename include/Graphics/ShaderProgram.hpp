#ifndef FUG_SHADER_PROGRAM_HPP
#define FUG_SHADER_PROGRAM_HPP

#include "Core/Resource.hpp"

#include "glLoadGen/gl_core_3_3.h"

namespace fug {
    class FUG_RESOURCE(ShaderProgram) {
    public:
        FUG_RESOURCE_INIT_DESTROY_DECL
        ShaderProgram(void);
        GLuint getId(void) const;
    private:
        GLuint programId_;
    };
}

#endif // FUG_SHADER_PROGRAM_HPP