#ifndef FUG_GRAPHICS_MESHCOMPONENT_HPP
#define FUG_GRAPHICS_MESHCOMPONENT_HPP


#include <Core/Component.hpp>
#include <Graphics/Mesh.hpp>
#include <Core/MathTypes.hpp>


namespace fug {

    class MeshComponent : public Component {
    public:
        MeshComponent(ResourcePointer<Mesh>& mesh,
                      const Matrix4Glf& transformation = Matrix4Glf::Identity());

        const Mesh& getMesh(void) const;
        ResourcePointer<Mesh> getMeshPointer(void) const;

        void setTransformation(const Matrix4Glf& transformation);
        void draw(const Matrix4Glf& view, const Matrix4Glf& proj) const;

    private:
        ResourcePointer<Mesh> mesh_;
        Matrix4Glf transformation_;
    };

} // namespace fug  


#endif // FUG_GRAPHICS_MESHCOMPONENT_HPP

