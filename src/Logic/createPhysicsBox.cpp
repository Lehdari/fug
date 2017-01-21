#include "Logic/createPhysicsBox.hpp"
#include "Logic/createBox2dBody.hpp"


namespace fug {

Box2dBodyComponent createPhysicsBox(b2BodyType type, b2Vec2 position, b2Vec2 halfSize,
    float density, float friction)
{
    b2PolygonShape shape;
    shape.SetAsBox(halfSize.x, halfSize.y);
    return createBox2dBody(Box2dBodyDefinition(type, &shape, position, density, friction));
}


}
