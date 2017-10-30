#ifndef FUG_GRAPHICS_SPRITEMATERIAL_INIT_HPP
#define FUG_GRAPHICS_SPRITEMATERIAL_INIT_HPP

#include <Core/ResourceManager.hpp>
#include <Graphics/SpriteMaterial.hpp>

#include <vector>
#include <string>


namespace fug {

    /// Initialization info struct
    struct SpriteMaterialInitInfo_Default {
        /*  1st sampler2D: diffuse  */
        std::vector<std::string> uniformSampler2DNames;

        /*  1st mat4: uModelToClip */
        std::vector<std::string> uniformMat4Names;
        
        /*  1st float: uSpriteW
            2nd float: uSpriteH
        */
        std::vector<std::string> uniformFloatNames;

        /*
            1st float: uFrameRow
            2nd float: uFrameColumn
         */
        std::vector<std::string> uniformGLintNames;
        
        GLuint spriteW;
        GLuint spriteH;
    
    };

    #include "SpriteMaterial_Init.tcc"

} // namespace fug


#endif // FUG_GRAPHICS_MATERIAL_INIT_DEFAULT_HPP
