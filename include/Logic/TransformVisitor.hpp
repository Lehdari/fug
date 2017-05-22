#ifndef FUG_TRANSFORM_VISITOR_HPP
#define FUG_TRANSFORM_VISITOR_HPP


#include "Core/Visitor.hpp"
#include "Logic/TransformComponent.hpp"
#include "Logic/MotionComponent.hpp"

namespace fug {
    
    class TransformVisitor : public Visitor<TransformVisitor, TransformComponent> {
    
    public:
        void operator()(TransformComponent&);

    };
}


#endif // FUG_TRANSFORM_VISITOR_HPP
