#ifndef FUG_CREATE_BOX2D_BODY_FACTORY_HPP
#define FUG_CREATE_BOX2D_BODY_FACTORY_HPP


#include "Logic/Box2dBodyDefinition.hpp"
#include "Logic/Box2dBodyComponent.hpp"

namespace fug {

    Box2dBodyComponent createBox2dBody(Box2dBodyDefinition def);

}


#endif // FUG_CREATE_BOX2D_BODY_FACTORY_HPP
