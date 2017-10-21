#ifndef FUG_GRAPHICS_RENDEROBJECT_HPP
#define FUG_GRAPHICS_RENDEROBJECT_HPP

#include <GL/glew.h>
#include <vector>
#include "Core/MathTypes.hpp"
#include "Graphics/Camera.hpp"

namespace fug {

struct RenderObject{
    GLint vao;
    uint32_t nIndices;
    std::vector<GLuint> textures;
    GLint shaderID;
    Vector3Glf specularColor;
    GLfloat specularExp;
    std::vector<GLint> uLocs_Sampler2D;
    std::vector<GLint> uLocs_Mat4;
    std::vector<GLint> uLocs_Vec3;
    std::vector<GLint> uLocs_Float;
    Matrix4Glf transform;
};

void renderObjects(std::vector<RenderObject>& objects, Camera& cam);

}

#endif // FUG_GRAPHICS_RENDEROBJECT_HPP
