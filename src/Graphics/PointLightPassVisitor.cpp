#include "Graphics/PointLightPassVisitor.hpp"

using namespace fug;

PointLightPassVisitor::PointLightPassVisitor(GBuffer& gBuffer,
                                             ResourcePointer<ShaderProgram> stencilShader,
                                             ResourcePointer<Mesh> sphereMesh,
                                             const Camera& cam,
                                             const std::vector<GLfloat>& hCorners) :
    _gBuffer(gBuffer),
    _stencilShader(stencilShader),
    _sphereMesh(sphereMesh),
    _cam(cam),
    _hCorners(hCorners)
{
    ;
}

bool PointLightPassVisitor::operator()(PointLightComponent& light)
{
    // Calculate and bind bounding sphere trasform
    Vector3Glf pos = light._position;
    Matrix4Glf translMat;
    translMat << 1.f, 0.f, 0.f, pos[0],
                 0.f, 1.f, 0.f, pos[1],
                 0.f, 0.f, 1.f, pos[2],
                 0.f, 0.f, 0.f,    1.f;
    float maxCol = fmax(fmax(light._color[0], light._color[1]), light._color[2]);
    float scale = (-light._attenLin + sqrt(light._attenLin * light._attenLin -
                   4 * light._attenExp * (light._attenConst - 256 * maxCol * light._directInt)))
                  /
                  (2 * light._attenExp);
    Matrix4Glf scaleMat;
    scaleMat << scale,   0.f,   0.f, 0.f,
                  0.f, scale,   0.f, 0.f,
                  0.f,   0.f, scale, 0.f,
                  0.f,   0.f,   0.f, 1.f;
    Matrix4Glf modelToClip = _cam.getProj() * _cam.getView() * translMat * scaleMat;

    // Perform the passes
    stencilPass(modelToClip);
    lightPass(light, modelToClip);

    return true;
}

void PointLightPassVisitor::stencilPass(const Matrix4Glf& modelToClip)
{
    // Bind stencil program and gBuffer
    glUseProgram(_stencilShader->getId());
    _gBuffer.bindStencilPass();

    // Setup rendering to stencil
    glEnable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);
    glClear(GL_STENCIL_BUFFER_BIT);
    glStencilFunc(GL_ALWAYS, 0, 0);
    glStencilOpSeparate(GL_BACK, GL_KEEP, GL_INCR_WRAP, GL_KEEP);
    glStencilOpSeparate(GL_FRONT, GL_KEEP, GL_DECR_WRAP, GL_KEEP);
    // Render bounding sphere to stencil
    glUniformMatrix4fv(glGetUniformLocation(_stencilShader.getId(), "uModelToClip"),
                       1, GL_FALSE, modelToClip.data());
    _sphereMesh->draw();
}

void PointLightPassVisitor::lightPass(PointLightComponent& light,
                                        const Matrix4Glf& modelToClip)
{
    // Bind light uniforms and gBuffer
    light.bind(_cam.getView());
    _gBuffer.bindLightPass();

    // Setup stencil
    glDisable(GL_DEPTH_TEST);
    glStencilFunc(GL_NOTEQUAL, 0, 0xFF);

    // Setup additive blending
    glEnable(GL_BLEND);
    glBlendEquation(GL_FUNC_ADD);
    glBlendFunc(GL_ONE, GL_ONE);

    glEnable(GL_CULL_FACE);
    glCullFace(GL_FRONT);

    // TODO: Figure out a cleaner way to do this
    GLuint shaderId = light.getShaderId();
    glUniform2fv(glGetUniformLocation(shaderId, "uCornerVecs"), 4, _hCorners.data());
    glUniformMatrix4fv(glGetUniformLocation(shaderId, "uModelToClip"),
                       1, GL_FALSE, modelToClip.data());
    _sphereMesh->draw();

    glCullFace(GL_BACK);
    glDisable(GL_BLEND);
}
