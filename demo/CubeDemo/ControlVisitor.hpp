#ifndef FUG_CONTROL_VISITOR_HPP
#define FUG_CONTROL_VISITOR_HPP


#include "Core/Visitor.hpp"
#include "Logic/TransformComponent.hpp"
#include "ControlMapComponent.hpp"

namespace fug {

    class ControlVisitor : public Visitor<ControlVisitor, TransformComponent, ControlMapComponent> {
    
    public:
        void operator()(TransformComponent&, ControlMapComponent&);

    private:
        float _move_amount = 0.35;
    
    };
}


#endif // FUG_CONTROL_VISITOR_HPP
