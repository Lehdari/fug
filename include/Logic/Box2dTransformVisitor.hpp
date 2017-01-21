#ifndef FUG_BOX2D_TRANSFORM_VISITOR_HPP
#define FUG_BOX2D_TRANSFORM_VISITOR_HPP


#include "Core/Visitor.hpp"
#include "Logic/Box2dBodyComponent.hpp"
#include "Logic/TransformComponent.hpp"


namespace fug {


    class Box2dTransformVisitor : public Visitor<Box2dTransformVisitor,
        Box2dBodyComponent, TransformComponent> {
    public:
        void operator()(Box2dBodyComponent& body, TransformComponent& transform);
    };

}


#endif // FUG_BOX2D_TRANSFORM_VISITOR_HPP
