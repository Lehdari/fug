#ifndef FUG_GRAPHICS_MESH_HPP
#define FUG_GRAPHICS_MESH_HPP



#include <GL/glew.h>
#include <Core/ResourceManager.hpp>
#include <Core/MathTypes.hpp>
#include <Graphics/Material.hpp>



namespace fug {

    class FUG_RESOURCE(Mesh) {
    public:
        //  Resource init and destroy template member function declarations
        FUG_RESOURCE_INIT_DESTROY_DECL

        Mesh(void);

        void draw(const Matrix4Glf& model, const Matrix4Glf& view, const Matrix4Glf& proj) const;
        const Material& getMaterial(void) const;
        ResourcePointer<Material> getMaterialPointer(void) const;

    private:
        ResourcePointer<Material> _material;

        GLuint _vertexArrayObjectId;

        unsigned _nIndices;

        GLuint _positionBufferId;
        GLuint _texCoordBufferId;
        GLuint _normalBufferId;
        GLuint _elementBufferId;
    };

} // namespace fug


#endif // FUG_GRAPHICS_MESH_HPP
