#ifndef FUG_GRAPHICS_VERTEXDATA_INIT_BINARY_HPP
#define FUG_GRAPHICS_VERTEXDATA_INIT_BINARY_HPP


#include <Core/ResourceManager.hpp>
#include <Graphics/VertexData.hpp>
#include <Core/Binary.hpp>

#include <map>
#include <cstring>


namespace fug {

    /// Initialization info struct
    struct VertexDataInitInfo_Binary {
        enum Source {
            SOURCE_BINARY_OBJ,      //  from .obj file
        } source;
    };

#include "VertexData_Init.tcc"

} // namespace fug


#endif // FUG_GRAPHICS_VERTEXDATA_INIT_BINARY_HPP
