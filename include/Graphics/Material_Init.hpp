#ifndef FUG_GRAPHICS_MATERIAL_INIT_HPP
#define FUG_GRAPHICS_MATERIAL_INIT_HPP

#include <Core/ResourceManager.hpp>
#include <Graphics/Material.hpp>

#include <vector>
#include <string>


namespace fug {

    /// Initialization info struct
    struct MaterialInitInfo_Default {
        Vector3Glf specularColor;
        float      specularExp;
    };

    #include "Material_Init.tcc"

} // namespace fug


#endif // FUG_GRAPHICS_MATERIAL_INIT_DEFAULT_HPP
