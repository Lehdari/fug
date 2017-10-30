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
        const std::vector<ResourcePointer<Texture>>& getTexturePtrs() const;
        const Vector3Glf& getSpecularColor() const;
        float getSpecularExp() const;

        const std::vector<GLint>& getUniformLocsSampler2D() const;
        const std::vector<GLint>& getUniformLocsMat4() const;
        const std::vector<GLint>& getUniformLocsVec3() const;
        const std::vector<GLint>& getUniformLocsFloat() const;

    private:
        ResourcePointer<ShaderProgram>          _shader;
        std::vector<ResourcePointer<Texture>>   _textures;
        Vector3Glf                              _specularColor;
        float                                   _specularExp;

        std::vector<GLint> _uniformLocations_Sampler2D;
        std::vector<GLint> _uniformLocations_Mat4;
        std::vector<GLint> _uniformLocations_Vec3;
        std::vector<GLint> _uniformLocations_Float;
    };

};


#endif // FUG_GRAPHICS_SPRITEMATERIAL_HPP
