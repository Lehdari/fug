#ifndef FUG_GRAPHICS_MATERIAL_HPP
#define FUG_GRAPHICS_MATERIAL_HPP

#include <GL/glew.h>
#include <Core/ResourceManager.hpp>
#include <Core/MathTypes.hpp>
#include <Graphics/ShaderProgram.hpp>
#include <Graphics/Texture.hpp>

#include <vector>

namespace fug {

    class FUG_RESOURCE(Material) {
    public:
        //  Resource init and destroy template member function declarations
        FUG_RESOURCE_INIT_DESTROY_DECL

        Material(void);

        const ResourcePointer<ShaderProgram>& getShaderProgPtr() const;
        const std::vector<std::pair<GLint, ResourcePointer<Texture>>>& getTextures() const;
        const std::vector<std::pair<GLint, Vector3Glf>>& getVec3s() const;
        const std::vector<std::pair<GLint, float>>& getFloats() const;

    private:
        ResourcePointer<ShaderProgram>                          _shader;
        std::vector<std::pair<GLint, ResourcePointer<Texture>>> _textures;
        std::vector<std::pair<GLint, Vector3Glf>>               _vec3s;
        std::vector<std::pair<GLint, float>>                    _floats;

    };

};


#endif // FUG_GRAPHICS_SPRITEMATERIAL_HPP
