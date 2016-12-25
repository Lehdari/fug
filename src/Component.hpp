#ifndef FUG_COMPONENT_HPP
#define FUG_COMPONENT_HPP


#include "Types.hpp"


namespace fug {


    class Component {
    public:
        friend class Scene;

    protected:
        CId  _id;
    };


}


#endif // FUG_COMPONENT_HPP
