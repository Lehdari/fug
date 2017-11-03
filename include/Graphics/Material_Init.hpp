#ifndef FUG_GRAPHICS_MATERIAL_INIT_HPP
#define FUG_GRAPHICS_MATERIAL_INIT_HPP

#include <Core/ResourceManager.hpp>
#include <Graphics/Material.hpp>

#include <string>
#include <tuple>
#include <vector>


namespace fug {

    /// Initialization info struct
    struct MaterialInitInfo_Default {
        std::vector<std::string> sampler2DUniforms;
        std::vector<std::pair<std::string, Vector3Glf>> vec3Uniforms;
        std::vector<std::pair<std::string, float>> floatUniforms;
    };

    #include "Material_Init.tcc"

} // namespace fug


#endif // FUG_GRAPHICS_MATERIAL_INIT_DEFAULT_HPP
