#include "Graphics/DirectionalLightPassVisitor.hpp"

using namespace fug;

DirectionalLightPassVisitor::DirectionalLightPassVisitor(ResourcePointer<Mesh> quadMesh,
                                                         const Camera& cam,
                                                         const std::vector<GLfloat>& hCornersBuf,
                                                         int currentMode) :
    _quadMesh(quadMesh),
    _cam(cam),
    _hCornersBuf(hCornersBuf),
    _currentMode(currentMode)
{
    glDepthMask(GL_FALSE);
    glDisable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendEquation(GL_FUNC_ADD);
    glBlendFunc(GL_ONE, GL_ONE);
    glClear(GL_COLOR_BUFFER_BIT);
}

bool DirectionalLightPassVisitor::operator()(DirectionalLightComponent& light) {
    light.bind(_cam.getView());
    // TODO: Figure out a cleaner way to do this
    GLuint shaderId = light.getShaderId();
    glUniform2fv(glGetUniformLocation(shaderId, "uCornerVecs"), 4, _hCornersBuf.data());
    glUniform1i(glGetUniformLocation(shaderId, "uOnlyDepth"), _currentMode == 1);
    glUniform1i(glGetUniformLocation(shaderId, "uOnlyDiffuse"), _currentMode == 2);
    glUniform1i(glGetUniformLocation(shaderId, "uOnlyNormal"), _currentMode == 3);
    glUniform1i(glGetUniformLocation(shaderId, "uOnlySpecular"), _currentMode == 4);
    _quadMesh->draw();
    return true;
}
