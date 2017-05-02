#ifndef FUG_TRANSFORM_VISITOR_HPP
#define FUG_TRANSFORM_VISITOR_HPP


#include "Core/Visitor.hpp"
#include "Logic/TransformComponent.hpp"
#include "MotionComponent.hpp"

namespace fug {
    
    class TransformVisitor : public Visitor<TransformVisitor, MotionComponent, TransformComponent> {
    
    public:
        void operator()(MotionComponent&, TransformComponent&);

    };
}


#endif // FUG_TRANSFORM_VISITOR_HPP
