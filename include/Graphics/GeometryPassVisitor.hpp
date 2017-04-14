#ifndef FUG_GRAPHICS_GEOMETRYPASSVISITOR_HPP
#define FUG_GRAPHICS_GEOMETRYPASSVISITOR_HPP

#include "Core/MathTypes.hpp"
#include "Core/Visitor.hpp"
#include "Logic/TransformComponent.hpp"
#include "Graphics/Camera.hpp"
#include "Graphics/GBuffer.hpp"
#include "Graphics/MeshComponent.hpp"

namespace fug {

    class GeometryPassVisitor : public Visitor<GeometryPassVisitor, MeshComponent,
                                        TransformComponent> {
    public:
        GeometryPassVisitor(const Camera& c);

        bool operator()(MeshComponent& mesh, TransformComponent& transform);

    private:
        Camera _cam;

    };

} // namespace fug

#endif // FUG_GRAPHICS_GEOMETRYPASSVISITOR_HPP
