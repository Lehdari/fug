#ifndef FUG_GRAPHICS_POINT_LIGHT_PASS_HPP
#define FUG_GRAPHICS_POINT_LIGHT_PASS_HPP

#include "Core/MathTypes.hpp"
#include "Core/Visitor.hpp"
#include "Graphics/Camera.hpp"
#include "Graphics/GBuffer.hpp"
#include "Graphics/Mesh.hpp"
#include "Graphics/PointLightComponent.hpp"
#include "Logic/TransformComponent.hpp"

namespace fug {

    class PointLightPass : public Visitor<PointLightPass, PointLightComponent, TransformComponent>
    {
    public:
        PointLightPass(const Camera& c, std::shared_ptr<GBuffer> gb,
                       const std::vector<GLfloat>& hCorners, const Vector2Glf& viewportSize,
                       ResourcePointer<ShaderProgram>& stencilProg);
        bool operator()(PointLightComponent& light, TransformComponent& t);

        Camera _cam;
        std::vector<GLfloat> _hCorners;
        Vector2Glf _viewportSize;
    private:
        bool drawStencil(PointLightComponent& light, TransformComponent& t);
        bool drawLight(PointLightComponent& light, TransformComponent& t);

        std::shared_ptr<GBuffer> _gBuffer;
        ResourcePointer<ShaderProgram> _stencilProg;

    };

} // namespace fug

#endif // FUG_GRAPHICS_POINT_LIGHT_PASS_HPP
