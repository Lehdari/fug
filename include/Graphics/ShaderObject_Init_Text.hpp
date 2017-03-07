#ifndef SHADER_OBJECT_INIT_TEXT_HPP
#define SHADER_OBJECT_INIT_TEXT_HPP

#include "Core/Log.hpp"
#include "Core/ResourceInitInfoMap.hpp"
#include "Core/Text.hpp"

#include "Graphics/ShaderObject.hpp"
#include "Graphics/GLenumMap.hpp"

namespace fug {
    struct ShaderObjectInitInfo_Text {
        GLenum type;
    };

    FUG_RESOURCE_INITINFO_INIT(ShaderObject, ShaderObjectInitInfo_Text)
    {
        initInfo.type = fug::getGLenum(json["shaderType"]);
    }

    FUG_RESOURCE_INIT(ShaderObject, ShaderObjectInitInfo_Text) {
        if (initResources.size() == 0) {
            objectId_ = 0;
            return;
        }
        auto src = FUG_RESOURCE_MANAGER.getResource<Text>(initResources[0]);
        FUG_LOG(LogLevel::Debug)("%s: get: %p\n", __func__, src.get());
        FUG_LOG(LogLevel::Debug)("res num: %lu\n", initResources[0]);
        FUG_LOG(LogLevel::Debug)("%s: resource pointer buffer: %p\n", __func__,
                                 src->getBufferPtr());
        const char* srcPtr = src->getBufferPtr();

        objectId_ = glCreateShader(initInfo.type);

        glShaderSource(objectId_, 1, &srcPtr, NULL);
        glCompileShader(objectId_);

        GLint compileStatus, infoLogLength;
        glGetShaderiv(objectId_, GL_COMPILE_STATUS, &compileStatus);

        if (compileStatus == GL_FALSE) {
            glGetShaderiv(objectId_, GL_INFO_LOG_LENGTH, &infoLogLength);
            char* infoLog = new char[infoLogLength];
            glGetShaderInfoLog(objectId_, infoLogLength, &infoLogLength, infoLog);
            FUG_LOG(LogLevel::Error)("%s", infoLog);
            glDeleteShader(objectId_);
            throw infoLog;
        }
    }
    FUG_RESOURCE_DESTROY(ShaderObject, ShaderObjectInitInfo_Text) {
        if (objectId_ != 0)
            glDeleteShader(objectId_);
    }
}

#endif //SHADER_OBJECT_INIT_TEXT_HPP
