#ifndef SHADER_OBJECT_INIT_BINARY_HPP
#define SHADER_OBJECT_INIT_BINARY_HPP

//#include "Core/ResourceManager.hpp"
#include "Graphics/ShaderObject.hpp"
#include "Core/Binary.hpp"

namespace fug {
    struct ShaderObjectInitInfo_Binary {
        enum Source {
            SOURCE_GLSL,    // Load from glsl
            SOURCE_BINARY   // Loaf from precompiled binary
        } source;
        GLenum type;
    };
    FUG_RESOURCE_INIT(ShaderObject, ShaderObjectInitInfo_Binary) { 
        if (initInfo.source != ShaderObjectInitInfo_Binary::SOURCE_GLSL)
            throw "ShaderObject: binary loading not implemented";
        if (initResources.size() == 0) {
            objectId_ = 0;
            return;
        }
        auto src = FUG_RESOURCE_MANAGER.getResource<Binary>(initResources[0]);
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
            glGetShaderiv(objectId_, infoLogLength, &infoLogLength);
            char* infoLog = new char[infoLogLength];
            glGetShaderInfoLog(objectId_, infoLogLength, NULL, infoLog);
            fprintf(stderr, "%s", infoLog);
            throw infoLog;
        }
    }
    FUG_RESOURCE_DESTROY(ShaderObject, ShaderObjectInitInfo_Binary) {
        if (objectId_ != 0)
            glDeleteShader(objectId_);
    }
}

#endif //SHADER_OBJECT_INIT_BINARY_HPP
