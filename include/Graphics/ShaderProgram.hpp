#ifndef FUG_SHADER_PROGRAM_HPP
#define FUG_SHADER_PROGRAM_HPP

#include "Core/Resource.hpp"
#include "Graphics/RenderingMatrixType.hpp"

#include <GL/glew.h>

namespace fug {
    class FUG_RESOURCE(ShaderProgram) {
    public:
        FUG_RESOURCE_INIT_DESTROY_DECL
        ShaderProgram(void);
        GLuint getId(void) const;
        const std::vector<GLint>& getSamplerLocations() const;
        const std::vector<GLint>& getUniformLocations() const;
        const std::vector<GLint>& getMatrixLocations() const;
    private:
        GLuint programId_;
        std::vector<GLint> _samplerLocations;
        std::vector<GLint> _uniformLocations;
        std::vector<GLint> _matrixLocations;
    };
}

#endif // FUG_SHADER_PROGRAM_HPP
