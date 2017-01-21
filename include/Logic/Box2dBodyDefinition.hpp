#ifndef FUG_BOX2D_BODY_DEFINITION_HPP
#define FUG_BOX2D_BODY_DEFINITION_HPP


#include "Box2D/Box2D.h"

namespace fug {

    class Box2dBodyDefinition {
    public:
        Box2dBodyDefinition(b2BodyType type, b2Shape* shape, b2Vec2 position, float density,
            float friction) :
            type(type),
            shape(shape),
            position(position),
            density(density)
        {}
          
          b2BodyType type;
          b2Shape* shape;
          b2Vec2 position;
          float density;
          float friction;
    };

}


#endif // FUG_BOX2D_BODY_DEFINITION_HPP
