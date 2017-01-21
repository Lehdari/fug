#ifndef FUG_GRAPHICS_SPRITEMESH_HPP
#define FUG_GRAPHICS_SPRITEMESH_HPP



#include "glLoadGen/gl_core_3_3.h"
#include <Core/ResourceManager.hpp>
#include <Core/MathTypes.hpp>
#include <Graphics/SpriteMaterial.hpp>



namespace fug {

    class FUG_RESOURCE(SpriteMesh) {
    public:
        //  Resource init and destroy template member function declarations
        FUG_RESOURCE_INIT_DESTROY_DECL

        SpriteMesh(void);

        void draw(const Matrix4Glf& mvp,
                  const GLint& frameRow, const GLint& frameColumn) const;
        void draw(const Matrix4Glf& model, const Matrix4Glf& camera,
                  const GLint& frameRow, const GLint& frameColumn) const;

        const SpriteMaterial& getMaterial(void) const;
        ResourcePointer<SpriteMaterial> getMaterialPointer(void) const;

    private:
        ResourcePointer<SpriteMaterial> _material;

        GLuint _vertexArrayObjectId;

        unsigned _nIndices;

        GLuint _positionBufferId;
        GLuint _elementBufferId;
    };

} // namespace fug


#endif // FUG_GRAPHICS_SPRITEMESH_HPP
