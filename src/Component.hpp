#ifndef FUG_COMPONENT_HPP
#define FUG_COMPONENT_HPP


#include "Types.hpp"
#include "Macros.hpp"
#include "SceneImplementation.hpp"


namespace fug {


    class Component {
    public:
        friend SceneImplementation;

        template <typename T_Component>
        static const CId& typeId(void);

    #ifndef FUG_DEBUG
    protected:
    #endif
        NId  _nodeId;

    private:
        static CId  _typeId;
    };


    template <typename T_Component>
    const CId& Component::typeId(void) {
        static CId typeId = _typeId++;
        return typeId;
    }


}


#endif // FUG_COMPONENT_HPP
