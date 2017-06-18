#ifndef FUG_GRAPHICS_POINTLIGHTPASSVISITOR_HPP
#define FUG_GRAPHICS_POINTLIGHTPASSVISITOR_HPP

#include "Core/MathTypes.hpp"
#include "Core/Visitor.hpp"
#include "Graphics/Camera.hpp"
#include "Graphics/GBuffer.hpp"
#include "Graphics/Mesh.hpp"
#include "Graphics/PointLightComponent.hpp"
#include "Graphics/ShaderProgram.hpp"

namespace fug {

    class PointLightPassVisitor : public Visitor<PointLightPassVisitor,
                                                 PointLightComponent> {
    public:
        PointLightPassVisitor(GBuffer& gBuffer, ResourcePointer<ShaderProgram> stencilShader,
                              ResourcePointer<Mesh> sphereMesh, const Camera& cam,
                              const std::vector<GLfloat>& hCorners);

        bool operator()(PointLightComponent& light);

    private:
        void stencilPass(const Matrix4Glf& modelToClip);
        void lightPass(PointLightComponent& light, const Matrix4Glf& modelToClip);

        GBuffer&                       _gBuffer;// TODO: Use pointer?
        ResourcePointer<ShaderProgram> _stencilShader;
        ResourcePointer<Mesh>          _sphereMesh;
        Camera                         _cam;
        std::vector<GLfloat>           _hCorners;

    };

} // namespace fug

#endif // FUG_GRAPHICS_POINTLIGHTPASSVISITOR_HPP
