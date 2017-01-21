#ifndef FUG_PLAYER_COMPONENT_HPP
#define FUG_PLAYER_COMPONENT_HPP


#include <cstdint>
#include "Core/Component.hpp"


namespace fug {

    class PlayerComponent : public Component {
    public:
        uint8_t playerId;
    };

}


#endif // FUG_PLAYER_COMPONENT_HPP
