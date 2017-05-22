#ifndef FUG_MOTION_VISITOR_HPP
#define FUG_MOTION_VISITOR_HPP


#include "Core/Visitor.hpp"
#include "Logic/MotionComponent.hpp"
#include "Logic/TransformComponent.hpp"

namespace fug {
    
    class MotionVisitor : public Visitor<MotionVisitor, MotionComponent, TransformComponent> {
    
    public:
        void operator()(MotionComponent&, TransformComponent&);

    private:
        void induceCircularMotion(MotionComponent&);
    };
}


#endif // FUG_MOTION_VISITOR_HPP
