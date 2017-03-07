#include "Graphics/GLenumMap.hpp"

#include <unordered_map>

namespace {

    const std::unordered_map<std::string, GLenum> GLenumsByString = {
        // Shader enums
        {"GL_VERTEX_SHADER", GL_VERTEX_SHADER},
        {"GL_GEOMETRY_SHADER", GL_GEOMETRY_SHADER},
        {"GL_FRAGMENT_SHADER", GL_FRAGMENT_SHADER},
        // Texture filter
        {"GL_NEAREST", GL_NEAREST},
        {"GL_LINEAR", GL_LINEAR},
        {"GL_NEAREST_MIPMAP_NEAREST", GL_NEAREST_MIPMAP_NEAREST},
        {"GL_LINEAR_MIPMAP_NEAREST", GL_LINEAR_MIPMAP_NEAREST},
        {"GL_NEAREST_MIPMAP_LINEAR", GL_NEAREST_MIPMAP_LINEAR},
        {"GL_LINEAR_MIPMAP_LINEAR", GL_LINEAR_MIPMAP_LINEAR},
        // Texture wrap
        {"GL_CLAMP_TO_EDGE", GL_CLAMP_TO_EDGE},
        {"GL_CLAMP_TO_BORDER", GL_CLAMP_TO_BORDER},
        {"GL_MIRRORED_REPEAT", GL_MIRRORED_REPEAT},
        {"GL_REPEAT", GL_REPEAT},
    };

}

const GLenum fug::getGLenum(const std::string& glenum) {
    return GLenumsByString.find(glenum)->second;
}
