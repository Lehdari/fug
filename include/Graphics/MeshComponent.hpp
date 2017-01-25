#ifndef FUG_GRAPHICS_MESHCOMPONENT_HPP
#define FUG_GRAPHICS_MESHCOMPONENT_HPP


#include <Graphics/Mesh.hpp>
#include <Core/MathTypes.hpp>


namespace fug {

    class MeshComponent {
    public:
        MeshComponent(ResourcePointer<Mesh>& mesh);

        const Mesh& getMesh(void) const;
        ResourcePointer<Mesh> getMeshPointer(void) const;

        void draw(const Matrix4Glf& transform, const Matrix4Glf& view, const Matrix4Glf& proj) const;

    private:
        ResourcePointer<Mesh> mesh_;
    };

} // namespace fug  


#endif // FUG_GRAPHICS_MESHCOMPONENT_HPP

