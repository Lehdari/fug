#ifndef SHADER_PROGRAM_INIT_DEFAULT_HPP
#define SHADER_PROGRAM_INIT_DEFAULT_HPP

#include "Core/ResourceInitInfoMap.hpp"

#include "Graphics/ShaderProgram.hpp"
#include "Graphics/ShaderObject.hpp"

namespace fug {
    struct ShaderProgramInitInfo_Default {
    };
    FUG_RESOURCE_INITINFO_INIT(ShaderProgram, ShaderProgramInitInfo_Default)
    {
    }
    FUG_RESOURCE_INIT(ShaderProgram, ShaderProgramInitInfo_Default)
    {
        if (initResources.size() == 0)
            return;
        programId_ = glCreateProgram();
        for (auto& initResourceId : initResources) {
            const auto &id = FUG_RESOURCE_MANAGER.getResource<ShaderObject>(initResourceId)->getId();
            glAttachShader(programId_, id);
        }
        glLinkProgram(programId_);
        GLint linkStatus, infoLogLength;
        glGetProgramiv(programId_, GL_LINK_STATUS, &linkStatus);

        if (linkStatus == GL_FALSE) {
            glGetShaderiv(programId_, GL_INFO_LOG_LENGTH, &infoLogLength);
            char *infoLog = new char[infoLogLength];
            glGetProgramInfoLog(programId_, infoLogLength, NULL, infoLog);
            fprintf(stderr, "%s", infoLog);
            throw infoLog;
        }
    }
    FUG_RESOURCE_DESTROY(ShaderProgram, ShaderProgramInitInfo_Default)
    {
        if (programId_ != 0)
            glDeleteProgram(programId_);
    }
}

#endif // SHADER_PROGRAM_INIT_DEFAULT_HPP
