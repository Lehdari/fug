#ifndef FUG_SHADER_PROGRAM_INIT_DEFAULT_HPP
#define FUG_SHADER_PROGRAM_INIT_DEFAULT_HPP

#include "ShaderProgram.hpp"

#include <GL/glew.h>

namespace fug {
    struct ShaderProgramInitInfo_Default;
    FUG_RESOURCE_INIT(ShaderProgram, ShaderProgramInitInfo_Default) {
        programId = glCreateProgram();
        /*
        for (const auto &initResourceId : initResources) {
            glAttachShader(programId, FUG_RESOURCE_MANGER.getResource<ShaderObject>(initResourceId).programId)
        }
        */
        
    }
}

#endif // FUG_SHADER_PROGRAM_INIT_DEFAULT_HPP
