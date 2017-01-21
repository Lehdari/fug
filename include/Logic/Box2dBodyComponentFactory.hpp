#ifndef FUG_BOX2D_BODY_COMPONENT_FACTORY_HPP
#define FUG_BOX2D_BODY_COMPONENT_FACTORY_HPP


#include <Box2D/Box2D.h>
#include "Logic/Box2dBodyComponent.hpp"

namespace fug {

    Box2dBodyComponent Box2dBodyComponentFactory(b2BodyDef bodyDef, b2FixtureDef fixtureDef);

}


#endif // FUG_BOX2D_BODY_COMPONENT_FACTORY_HPP
