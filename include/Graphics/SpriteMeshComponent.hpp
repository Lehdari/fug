#ifndef FUG_GRAPHICS_SPRITEMESHCOMPONENT_HPP
#define FUG_GRAPHICS_SPRITEMESHCOMPONENT_HPP


#include <Core/Component.hpp>
#include <Graphics/SpriteMesh.hpp>
#include <Core/MathTypes.hpp>


namespace fug {

    class SpriteMeshComponent : public Component {
    public:
        SpriteMeshComponent(ResourcePointer<SpriteMesh>& mesh);

        const SpriteMesh& getMesh(void) const;
        ResourcePointer<SpriteMesh> getMeshPointer(void) const;

        void draw(const Matrix4Glf& transform, const Matrix4Glf& camera,
                  const GLint& frameRow, const GLint& frameColumn) const;

    private:
        ResourcePointer<SpriteMesh> _mesh;
    };

} // namespace fug 


#endif // FUG_GRAPHICS_SPRITEMESHCOMPONENT_HPP

