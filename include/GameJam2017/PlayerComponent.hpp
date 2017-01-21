#ifndef FUG_PLAYER_COMPONENT_HPP
#define FUG_PLAYER_COMPONENT_HPP


#include <cstdint>
#include "Core/Component.hpp"


namespace fug {

    class PlayerComponent : public Component {
    public:
        PlayerComponent(uint8_t id) :
            playerId(id)
        {}
        PlayerComponent() :
            playerId(0)
        {}
        
        uint8_t playerId;
    };

}


#endif // FUG_PLAYER_COMPONENT_HPP
