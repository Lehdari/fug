#ifndef FUG_GRAPHICS_GBUFFER_HPP
#define FUG_GRAPHICS_GBUFFER_HPP

#include <GL/glew.h>
#include <vector>

namespace fug {

    class GBuffer {
    public:
        GBuffer(GLsizei resX, GLsizei resY, const std::vector<GLint>& sizedFormats,
                const std::vector<GLint>& baseFormats);
        ~GBuffer();

        void resize(GLsizei resX, GLsizei resY);
        void bindWrite();
        void bindRead();

    private:
        GLuint              _fbo;
        std::vector<GLuint> _textures;
        GLuint              _finalTexture;
        GLuint              _depthTexture;
        std::vector<GLint>  _sizedFormats;
        std::vector<GLint>  _baseFormats;

    };

} // namespace fug

#endif // FUG_GRAPHICS_GBUFFER_HPP
