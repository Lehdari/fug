#ifndef FUG_COMPONENT_HPP
#define FUG_COMPONENT_HPP


#include "Types.hpp"
#include "Scene.hpp"


namespace fug {


    class Component {
    public:
        friend SceneImplementation;

    protected:
        NId  _nodeId;;
    };


}


#endif // FUG_COMPONENT_HPP
