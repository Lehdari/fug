#ifndef FUG_BOX2D_TRANSFORM_VISITOR_HPP
#define FUG_BOX2D_TRANSFORM_VISITOR_HPP


#include "Core/Visitor.hpp"
#include "Logic/Box2dBodyComponent.hpp"
#include "Logic/TransformComponent.hpp"


namespace fug {


    class Box2dTransformVisitor : public Visitor<Box2dTransformVisitor,
        TransformComponent, Box2dBodyComponent> {
    public:
        void operator()(TransformComponent& transform, Box2dBodyComponent& body);
    };

}


#endif // FUG_BOX2D_TRANSFORM_VISITOR_HPP
