#include "Graphics/GBuffer.hpp"

using namespace fug;

GBuffer::GBuffer(GLsizei resX, GLsizei resY, std::vector<GLint> sizedFormats,
                 std::vector<GLint> baseFormats)
{
    // TODO: Better checks
    if (resX == 0 || resY == 0)
        throw "Trying to create gbuffer with 0 width or height!";
    if (sizedFormats.size() == 0)
        throw "Trying to create an empty gbuffer!";
    if (sizedFormats.size() != baseFormats.size())
        throw "Mismatching format vectors in GBufferInitInfo!";

    // Generate and bind a new fbo
    glGenFramebuffers(1, &_fbo);
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, _fbo);

    // Generate textures
    _textures.resize(sizedFormats.size());
    glGenTextures(_textures.size(), _textures.data());
    glGenTextures(1, &_depthTexture);
    glGenTextures(1, &_finalTexture);

    for (auto i = 0u ; i < _textures.size() ; i++) {
        glBindTexture(GL_TEXTURE_2D, _textures[i]);
        glTexImage2D(GL_TEXTURE_2D, 0, sizedFormats[i], resX,
                     resY, 0, baseFormats[i], GL_FLOAT, NULL);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i,
                               GL_TEXTURE_2D, _textures[i], 0);
    }

    // Generate depth texture
    glBindTexture(GL_TEXTURE_2D, _depthTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32F, resX,
                 resY, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT,
                           GL_TEXTURE_2D, _depthTexture, 0);

    // Generate final texture
    glBindTexture(GL_TEXTURE_2D, _finalTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, resX, resY, 0, GL_RGB, GL_FLOAT, NULL);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + _textures.size(),
                           GL_TEXTURE_2D, _finalTexture, 0);

    GLenum Status = glCheckFramebufferStatus(GL_FRAMEBUFFER);

    if (Status != GL_FRAMEBUFFER_COMPLETE)
        throw "GBuffer initialization failed"; // TODO: add status to throw

    // Bind default fbo
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
}

GBuffer::~GBuffer()
{
    if (_fbo != 0) glDeleteFramebuffers(1, &_fbo);
    if (_textures.size() != 0) glDeleteTextures(_textures.size(), _textures.data());
    if (_depthTexture != 0) glDeleteTextures(1, &_depthTexture);
    if (_finalTexture != 0) glDeleteTextures(1, &_finalTexture);
}

void GBuffer::startFrame()
{
    // Clear final texture
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, _fbo);
    glDrawBuffer(GL_COLOR_ATTACHMENT0 + _textures.size());
    glClear(GL_COLOR_BUFFER_BIT);
}

void GBuffer::bindGeometryPass()
{
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, _fbo);

    std::vector<GLenum> drawBuffers;
    for (auto i = 0u; i < _textures.size(); ++i)
        drawBuffers.emplace_back(GL_COLOR_ATTACHMENT0 + i);

    glDrawBuffers(drawBuffers.size(), drawBuffers.data());
}

void GBuffer::bindLightPass()
{
    // Bind final texture for write
    glDrawBuffer(GL_COLOR_ATTACHMENT0 + _textures.size());

    // Bind other textures for read
    for (auto i = 0u; i < _textures.size(); ++i) {
        glActiveTexture(GL_TEXTURE0 + i);
        glBindTexture(GL_TEXTURE_2D, _textures[i]);
    }
}

void GBuffer::bindFinalPass()
{
    // Bind default fbo for write
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
    // Bind final texture for read
    glBindFramebuffer(GL_READ_FRAMEBUFFER, _fbo);
    glReadBuffer(GL_COLOR_ATTACHMENT0 + _textures.size());
}
