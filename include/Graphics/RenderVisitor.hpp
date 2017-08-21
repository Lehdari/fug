#ifndef FUG_GRAPHICS_RENDER_VISITOR_HPP
#define FUG_GRAPHICS_RENDER_VISITOR_HPP


#include "Core/MathTypes.hpp"
#include "Core/Visitor.hpp"
#include "Logic/TransformComponent.hpp"
#include "Graphics/MeshComponent.hpp"
#include "Graphics/CameraComponent.hpp"

namespace fug {

    class RenderVisitor : public Visitor<RenderVisitor, MeshComponent, TransformComponent>{
    public:
        RenderVisitor();

        bool operator()(MeshComponent& mesh, TransformComponent& transform);

        bool initCamera();

    private:
        const CameraComponent* _cam;

    };

} // namespace fug


#endif // FUG_GRAPHICS_RENDERER_HPP
