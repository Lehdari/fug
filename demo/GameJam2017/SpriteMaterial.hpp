#ifndef FUG_GRAPHICS_SPRITEMATERIAL_HPP
#define FUG_GRAPHICS_SPRITEMATERIAL_HPP

#include <GL/glew.h>
#include <Core/ResourceManager.hpp>
#include <Core/MathTypes.hpp>
#include <Graphics/ShaderProgram.hpp>
#include <Graphics/Texture.hpp>

#include <vector>

namespace fug {

    class FUG_RESOURCE(SpriteMaterial) {
    public:
        //  Resource init and destroy template member function declarations
        FUG_RESOURCE_INIT_DESTROY_DECL

        SpriteMaterial(void);

        void useMaterial(const Matrix4Glf& mvp,
                         const GLint& frameRow, const GLint& frameColumn) const;
        //  note ordering in initialization info (model matrix name first)
        //  also known as world and VP matrices
        void useMaterial(const Matrix4Glf& model, const Matrix4Glf& camera,
                         const GLint& frameRow, const GLint& frameColumn) const;

        GLuint getShaderId(void) const;

    private:
        ResourcePointer<ShaderProgram>          _shader;
        std::vector<ResourcePointer<Texture>>   _textures;
        GLfloat                                 _spriteW;
        GLfloat                                 _spriteH;

        std::vector<GLint> _uniformLocations_Sampler2D;
        std::vector<GLint> _uniformLocations_Mat4;
        std::vector<GLint> _uniformLocations_Float;
        std::vector<GLint> _uniformLocations_Int;

        void bindTextures(void) const;
    };

};


#endif // FUG_GRAPHICS_SPRITEMATERIAL_HPP
