#ifndef FUG_CHARACTER_INFO_COMPONENT_HPP
#define FUG_CHARACTER_INFO_COMPONENT_HPP


#include <cstdint>
#include <Eigen/Dense>
#include "Core/Component.hpp"


namespace fug {

    class CharacterInfoComponent : public Component {
    public:
        uint16_t characterId;
        bool isPlayer;
    };

}


#endif // FUG_CHARACTER_INFO_COMPONENT_HPP
