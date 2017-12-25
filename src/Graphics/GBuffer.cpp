#include "Graphics/GBuffer.hpp"

#include "Core/Log.hpp"

using namespace fug;

GBuffer::GBuffer(GLsizei resX, GLsizei resY, const std::vector<GLint>& sizedFormats,
                 const std::vector<GLint>& baseFormats) :
    _sizedFormats(sizedFormats),
    _baseFormats(baseFormats)
{
    if (resX == 0 || resY == 0) {
        FUG_LOG(LogLevel::Error)("GBuffer: trying to create with 0 width or height\n");
        throw;
    }
    if (_sizedFormats.size() == 0) {
        FUG_LOG(LogLevel::Error)("GBuffer: trying to create an empty gbuffer\n");
        throw;
    }
    if (_sizedFormats.size() != _baseFormats.size()) {
        FUG_LOG(LogLevel::Error)("GBuffer: format vectors mismatch\n");
        throw;
    }

    // Generate and bind a new fbo
    glGenFramebuffers(1, &_fbo);
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, _fbo);

    // Generate textures
    _textures.resize(sizedFormats.size());
    glGenTextures(_textures.size(), _textures.data());

    // Generate texture storage and bind to color attatchments in order
    for (auto i = 0u ; i < _textures.size() ; i++) {
        glBindTexture(GL_TEXTURE_2D, _textures[i]);
        glTexImage2D(GL_TEXTURE_2D, 0, _sizedFormats[i], resX, resY, 0, _baseFormats[i], GL_FLOAT, NULL);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D, _textures[i], 0);
        _drawBuffers.emplace_back(GL_COLOR_ATTACHMENT0 + i);
    }

    // Generate depth texture storage and bind to depth attatchment
    glGenTextures(1, &_depthTexture);
    glBindTexture(GL_TEXTURE_2D, _depthTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH32F_STENCIL8, resX, resY, 0, GL_DEPTH_STENCIL, GL_FLOAT_32_UNSIGNED_INT_24_8_REV, NULL);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, _depthTexture, 0);

    // Generate texture for final image
    _finalAttachment = _drawBuffers.back() + 1;
    glGenTextures(1, &_finalTexture);
    glBindTexture(GL_TEXTURE_2D, _finalTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, resX, resY, 0, GL_RGB, GL_FLOAT, NULL);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glFramebufferTexture2D(GL_FRAMEBUFFER, _finalAttachment, GL_TEXTURE_2D, _finalTexture, 0);

    // Verify framebuffer status
    GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
    if (status != GL_FRAMEBUFFER_COMPLETE) {
        FUG_LOG(LogLevel::Error)("GBuffer: framebuffer initialization failed\n");
        FUG_LOG(LogLevel::Error)("Status: %i\n", status);
        throw;
    }

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

void GBuffer::resize(GLsizei resX, GLsizei resY)
{
    // Resize generic textures
    for (auto i = 0u ; i < _textures.size() ; i++) {
        glBindTexture(GL_TEXTURE_2D, _textures[i]);
        glTexImage2D(GL_TEXTURE_2D, 0, _sizedFormats[i], resX, resY, 0, _baseFormats[i], GL_FLOAT, NULL);
    }
    // Resize depth texture
    glBindTexture(GL_TEXTURE_2D, _depthTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH32F_STENCIL8, resX, resY, 0, GL_DEPTH_STENCIL, GL_FLOAT_32_UNSIGNED_INT_24_8_REV, NULL);
    // Resize final texture
    glBindTexture(GL_TEXTURE_2D, _finalTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, resX, resY, 0, GL_RGB, GL_FLOAT, NULL);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void GBuffer::clearFinal()
{
    // Clear the final texture, should be done at the start of each frame
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, _fbo);
    glDrawBuffer(_finalAttachment);
    glClear(GL_COLOR_BUFFER_BIT);
}

void GBuffer::bindGeometryPass()
{
    // Bind buffers for geometry pass
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, _fbo);
    if (_drawBuffers.size() != 0)
        glDrawBuffers(_drawBuffers.size(), _drawBuffers.data());

}

void GBuffer::bindStencilPass()
{
    // Unbind buffers for (light) stencil pass
    glDrawBuffer(GL_NONE);
}

void GBuffer::bindLightPass()
{
    // Bind buffers for light pass
    glDrawBuffer(_finalAttachment);

    for (auto i = 0u ; i < _textures.size(); i++) {
        glActiveTexture(GL_TEXTURE0 + i);
        glBindTexture(GL_TEXTURE_2D, _textures[i]);
    }
}

void GBuffer::bindFinalRead()
{
    // Bind final texture for blit
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
    glBindFramebuffer(GL_READ_FRAMEBUFFER, _fbo);
    glReadBuffer(_finalAttachment);
}
