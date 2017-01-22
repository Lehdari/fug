#ifndef FUG_GRAPHICS_MATERIAL_INIT_HPP
#define FUG_GRAPHICS_MATERIAL_INIT_HPP

#include <Core/ResourceManager.hpp>
#include <Graphics/Material.hpp>

#include <vector>
#include <string>


namespace fug {

    /// Initialization info struct
    struct MaterialInitInfo_Default {
        /*  1st sampler2D: diffuse  */
        std::vector<std::string> uniformSampler2DNames;

        /*  1st mat4: uModelToClip
            2nd mat4: uModelToCam  
            3rd mat4: uNormalToCam */
        std::vector<std::string> uniformMat4Names;

        /* 1st vec3: uSpecularCol */
        std::vector<std::string> uniformVec3Names;

        /*  1st float: uSpecularExo*/
        std::vector<std::string> uniformFloatNames;
    
        Vector3Glf specularColor;
        float      specularExp;
    };

    #include "Material_Init.tcc"

} // namespace fug


#endif // FUG_GRAPHICS_MATERIAL_INIT_DEFAULT_HPP
