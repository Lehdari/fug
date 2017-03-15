#ifndef FUG_GRAPHICS_VERTEXDATA_INIT_UVSPHERE_HPP
#define FUG_GRAPHICS_VERTEXDATA_INIT_UVSPHERE_HPP


#include <Core/ResourceManager.hpp>
#include <Graphics/VertexData.hpp>
#include <Core/Text.hpp>

#include <map>
#include <cstring>


namespace fug {

    /// Initialization info struct
    struct VertexDataInitInfo_UVSphere {
        uint32_t segments;
        uint32_t rings;
    };

#include "VertexData_Init_UVSphere.tcc"

} // namespace fug


#endif // FUG_GRAPHICS_VERTEXDATA_INIT_UVSPHERE_HPP
