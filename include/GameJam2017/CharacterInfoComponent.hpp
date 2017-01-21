#ifndef FUG_CHARACTER_INFO_COMPONENT_HPP
#define FUG_CHARACTER_INFO_COMPONENT_HPP


#include "Core/Component.hpp"


namespace fug {

    class CharacterInfoComponent : public Component {
    public:
        CharacterInfoComponent() :
            placeholder(false)
        {}
        
        bool placeholder;
    };

}


#endif // FUG_CHARACTER_INFO_COMPONENT_HPP
