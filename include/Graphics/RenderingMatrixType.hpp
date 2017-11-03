#ifndef FUG_GRAPHICS_RENDERING_MATRIX_TYPE_HPP
#define FUG_GRAPHICS_RENDERING_MATRIX_TYPE_HPP

#include <GL/glew.h>
#include <string>
#include <vector>

namespace fug {

    enum class RenderingMatrixType : size_t {
        Model = 0,
        View = 1,
        Projection = 2,
        ModelToView = 3,
        ModelToClip = 4,
        NormalToView = 5,
        TYPE_COUNT = 6
    };

    RenderingMatrixType getRenderingMatrixType(const std::string& matrixType);
    std::vector<GLint> initRenderingMatrixLocations();

} // namespace fug

#endif // FUG_GRAPHICS_RENDERING_MATRIX_TYPE_HPP
