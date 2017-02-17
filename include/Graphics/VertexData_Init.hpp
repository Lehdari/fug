#ifndef FUG_GRAPHICS_VERTEXDATA_INIT_HPP
#define FUG_GRAPHICS_VERTEXDATA_INIT_HPP


#include <Core/ResourceManager.hpp>
#include <Graphics/VertexData.hpp>
#include <Core/Text.hpp>

#include <map>
#include <cstring>


namespace fug {

    /// Initialization info struct
    struct VertexDataInitInfo_Text {
        enum Source {
            SOURCE_BINARY_OBJ,      //  from .obj file
        } source;
    };

#include "VertexData_Init.tcc"

} // namespace fug


#endif // FUG_GRAPHICS_VERTEXDATA_INIT_HPP
