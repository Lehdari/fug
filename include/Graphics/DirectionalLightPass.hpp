#ifndef FUG_GRAPHICS_DIRECTIONAL_LIGHT_PASS_HPP
#define FUG_GRAPHICS_DIRECTIONAL_LIGHT_PASS_HPP

#include "Core/MathTypes.hpp"
#include "Core/Visitor.hpp"
#include "Graphics/Camera.hpp"
#include "Graphics/DirectionalLightComponent.hpp"
#include "Graphics/Mesh.hpp"

namespace fug {

    // NOTE: a second component here containing animation frame info!!
    class DirectionalLightPass : public Visitor<DirectionalLightPass, DirectionalLightComponent> {
    public:
        DirectionalLightPass(const ResourcePointer<Mesh>& quadMesh, const Matrix4Glf& normalToView,
                             const std::vector<GLfloat>& hCorners, const Vector2Glf& viewportSize);
        bool operator()(DirectionalLightComponent& light);

        void initPass() const;

        Matrix4Glf            _normalToView;
        std::vector<GLfloat>  _hCorners;
        Vector2Glf            _viewportSize;
    private:
        ResourcePointer<Mesh> _quadMesh;

    };

} // namespace fug

#endif // FUG_GRAPHICS_DIRECTIONAL_LIGHT_PASS_HPP
