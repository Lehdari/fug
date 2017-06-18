#ifndef FUG_GRAPHICS_DIRECTIONALLIGHTPASSVISITOR_HPP
#define FUG_GRAPHICS_DIRECTIONALLIGHTPASSVISITOR_HPP

#include "Core/MathTypes.hpp"
#include "Core/Visitor.hpp"
#include "Graphics/Camera.hpp"
#include "Graphics/DirectionalLightComponent.hpp"
#include "Graphics/Mesh.hpp"

namespace fug {

    class DirectionalLightPassVisitor : public Visitor<DirectionalLightPassVisitor,
                                                       DirectionalLightComponent> {
    public:
        DirectionalLightPassVisitor(ResourcePointer<Mesh> quadMesh,
                                    const Camera& cam,
                                    const std::vector<GLfloat>& _hCornersBuf,
                                    int _currentMode);

        bool operator()(DirectionalLightComponent& light);

    private:
        ResourcePointer<Mesh> _quadMesh;
        Camera                _cam;
        std::vector<GLfloat>  _hCornersBuf;
        int                   _currentMode;

    };

} // namespace fug

#endif // FUG_GRAPHICS_DIRECTIONALLIGHTPASSVISITOR_HPP
