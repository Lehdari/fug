#ifndef FUG_PLAYER_INFO_COMPONENT_HPP
#define FUG_PLAYER_INFO_COMPONENT_HPP


#include <cstdint>
#include "Core/Component.hpp"


namespace fug {

    class PlayerInfoComponent : public Component {
    public:
        // 0 if NPC, > 0 if human
        uint8_t playerId;
    };

}


#endif // FUG_PLAYER_INFO_COMPONENT_HPP
