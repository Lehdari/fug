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

        void useMaterial(const Matrix4Glf& model, const Matrix4Glf& vie, const Matrix4Glf& proj) const;

        GLuint getShaderId(void) const;

    private:
        ResourcePointer<ShaderProgram>          _shader;
        std::vector<ResourcePointer<Texture>>   _textures;
        Vector3Glf                              _specularColor;
        float                                   _specularExp;

        std::vector<GLint> _uniformLocations_Sampler2D;
        std::vector<GLint> _uniformLocations_Mat4;
        std::vector<GLint> _uniformLocations_Vec3;
        std::vector<GLint> _uniformLocations_Float;

        void bindTextures(void) const;
    };

};


#endif // FUG_GRAPHICS_SPRITEMATERIAL_HPP
