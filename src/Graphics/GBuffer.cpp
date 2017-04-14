#include "Graphics/GBuffer.hpp"

using namespace fug;

GBuffer::GBuffer(GLsizei resX, GLsizei resY, const std::vector<GLint>& sizedFormats,
                 const std::vector<GLint>& baseFormats) :
    _sizedFormats(sizedFormats),
    _baseFormats(baseFormats)
{
    // TODO: Better checks
    if (resX == 0 || resY == 0)
        throw "Trying to create gbuffer with 0 width or height!";
    if (_sizedFormats.size() == 0)
        throw "Trying to create an empty gbuffer!";
    if (_sizedFormats.size() != _baseFormats.size())
        throw "Mismatching format vectors in GBufferInitInfo!";

    // Generate and bind a new fbo
    glGenFramebuffers(1, &_fbo);
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, _fbo);

    // Generate textures
    std::vector<GLenum> drawBuffers;
    _textures.resize(sizedFormats.size());
    glGenTextures(_textures.size(), _textures.data());
    glGenTextures(1, &_depthTexture);

    for (auto i = 0u ; i < _textures.size() ; i++) {
        glBindTexture(GL_TEXTURE_2D, _textures[i]);
        glTexImage2D(GL_TEXTURE_2D, 0, _sizedFormats[i], resX,
                     resY, 0, _baseFormats[i], GL_FLOAT, NULL);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i,
                               GL_TEXTURE_2D, _textures[i], 0);
        drawBuffers.emplace_back(GL_COLOR_ATTACHMENT0 + i);
    }

    // Generate depth texture
    glBindTexture(GL_TEXTURE_2D, _depthTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32F, resX,
                 resY, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT,
                           GL_TEXTURE_2D, _depthTexture, 0);

    if (drawBuffers.size() != 0)
        glDrawBuffers(drawBuffers.size(), drawBuffers.data());

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
}

void GBuffer::resize(GLsizei resX, GLsizei resY)
{
    for (auto i = 0u ; i < _textures.size() ; i++) {
        glBindTexture(GL_TEXTURE_2D, _textures[i]);
        glTexImage2D(GL_TEXTURE_2D, 0, _sizedFormats[i], resX,
                     resY, 0, _baseFormats[i], GL_FLOAT, NULL);
    }
}

void GBuffer::bindWrite()
{
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, _fbo);
}

void GBuffer::bindRead()
{
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);

    for (auto i = 0u ; i < _textures.size(); i++) {
        glActiveTexture(GL_TEXTURE0 + i);
        glBindTexture(GL_TEXTURE_2D, _textures[i]);
    }
}
