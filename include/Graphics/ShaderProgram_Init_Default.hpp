#ifndef SHADER_PROGRAM_INIT_DEFAULT_HPP
#define SHADER_PROGRAM_INIT_DEFAULT_HPP

#include "Core/Log.hpp"
#include "Core/ResourceInitInfoMap.hpp"

#include "Graphics/ShaderProgram.hpp"
#include "Graphics/ShaderObject.hpp"

#include <tuple>

namespace fug {
    struct ShaderProgramInitInfo_Default {
        std::vector<std::pair<std::string, std::string>> matrixNames;
    };
    FUG_RESOURCE_INITINFO_INIT(ShaderProgram, ShaderProgramInitInfo_Default)
    {
        if (json.find("matrixNames") != json.end()) {
            for (auto it = json["matrixNames"].begin(); it != json["matrixNames"].end(); it++)
                initInfo.matrixNames.push_back({it.key(), it.value().get<std::string>()});
        }
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
            FUG_LOG(LogLevel::Error)("%s\n", infoLog);
            throw infoLog;
        }

        // Fetch uniform locations
        _matrixLocations = initRenderingMatrixLocations();
        for (auto& matrix : initInfo.matrixNames)
            _matrixLocations[static_cast<size_t>(getRenderingMatrixType(matrix.first))] =
                glGetUniformLocation(programId_, matrix.second.c_str());
    }
    FUG_RESOURCE_DESTROY(ShaderProgram, ShaderProgramInitInfo_Default)
    {
        if (programId_ != 0)
            glDeleteProgram(programId_);
    }
}

#endif // SHADER_PROGRAM_INIT_DEFAULT_HPP
