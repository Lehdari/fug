#ifndef FUG_GRAPHICS_SPRITEMESHCOMPONENT_HPP
#define FUG_GRAPHICS_SPRITEMESHCOMPONENT_HPP


#include "Graphics/SpriteMesh.hpp"
#include "Core/MathTypes.hpp"


namespace fug {

    class SpriteMeshComponent {
    public:
        SpriteMeshComponent(ResourcePointer<SpriteMesh>& mesh);

        const ResourcePointer<SpriteMesh>& getMeshPointer(void) const;

        void draw(const Matrix4Glf& transform, const Matrix4Glf& camera,
                  const GLint& frameRow, const GLint& frameColumn) const;

    private:
        ResourcePointer<SpriteMesh> _mesh;
    };

} // namespace fug


#endif // FUG_GRAPHICS_SPRITEMESHCOMPONENT_HPP

