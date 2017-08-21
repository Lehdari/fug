#ifndef FUG_GRAPHICS_CAMERA_VISITOR_HPP
#define FUG_GRAPHICS_CAMERA_VISITOR_HPP

#include "Core/Macros.hpp"
#include "CameraComponent.hpp"
#include "Logic/TransformComponent.hpp"
#include "Core/Visitor.hpp"

namespace fug {

    class CameraVisitor : public Visitor<CameraVisitor, CameraComponent, TransformComponent> {
    public:
        CameraVisitor() {};

        bool operator()(CameraComponent&, TransformComponent&);

    private:
        void orientation(CameraComponent&, TransformComponent&);
        void projection(CameraComponent&);
    };

} // namespace fug


#endif // FUG_GRAPHICS_CAMERA_VISITOR_HPP
