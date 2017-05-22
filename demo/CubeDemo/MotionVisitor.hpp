#ifndef FUG_MOTION_VISITOR_HPP
#define FUG_MOTION_VISITOR_HPP


#include "Core/Visitor.hpp"
#include "MotionComponent.hpp"

namespace fug {
    
    class MotionVisitor : public Visitor<MotionVisitor, MotionComponent> {
    
    public:
        void operator()(MotionComponent&);

    private:
        void induceCircularMotion(MotionComponent&);
    };
}


#endif // FUG_MOTION_VISITOR_HPP
