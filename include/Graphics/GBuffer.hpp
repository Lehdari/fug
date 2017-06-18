#ifndef FUG_GRAPHICS_GBUFFER_HPP
#define FUG_GRAPHICS_GBUFFER_HPP

#include <GL/glew.h>
#include <vector>

namespace fug {

    class GBuffer {
    public:
        GBuffer(GLsizei resX, GLsizei resY, std::vector<GLint> sizedFormats,
                std::vector<GLint> baseFormats);
        ~GBuffer();

        void startFrame();
        void bindGeometryPass();
        void bindStencilPass();
        void bindLightPass();
        void bindFinalPass();

    private:
        GLuint _fbo;
        std::vector<GLuint> _textures;
        GLuint _depthTexture;
        GLuint _finalTexture;

    };

};

#endif // FUG_GRAPHICS_GBUFFER_HPP
