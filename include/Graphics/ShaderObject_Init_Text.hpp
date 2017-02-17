#ifndef SHADER_OBJECT_INIT_TEXT_HPP
#define SHADER_OBJECT_INIT_TEXT_HPP

#include "Graphics/ShaderObject.hpp"
#include "Core/Text.hpp"

namespace fug {
    struct ShaderObjectInitInfo_Text {
        GLenum type;
    };
    FUG_RESOURCE_INITINFO_INIT(ShaderObject, ShaderObjectInitInfo_Text)
    {
        /* TODO */
        static struct ShaderObjectInitInfo_Text initInfo;
        return initInfo;
    }
    FUG_RESOURCE_INIT(ShaderObject, ShaderObjectInitInfo_Text) {
        if (initResources.size() == 0) {
            objectId_ = 0;
            return;
        }
        auto src = FUG_RESOURCE_MANAGER.getResource<Text>(initResources[0]);
        printf("%s: get: %p\n", __func__, src.get());
        printf("res num: %lu\n", initResources[0]);
        printf("%s: resource pointer buffer: %p\n", __func__, src->getBufferPtr());
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
            fprintf(stderr, "%s", infoLog);
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
