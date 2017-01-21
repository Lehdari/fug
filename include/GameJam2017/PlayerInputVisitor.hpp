#ifndef FUG_PLAYER_INPUT_VISITORS_HPP
#define FUG_PLAYER_INPUT_VISITORS_HPP


#include "Core/Visitor.hpp"
#include "GameJam2017/CharacterStateComponent.hpp"
#include "GameJam2017/CharacterInfoComponent.hpp"
#include "GameJam2017/PlayerInfoComponent.hpp"


namespace fug {


    class PlayerInputVisitor : public Visitor<PlayerInputVisitor,
        CharacterStateComponent, CharacterInfoComponent, PlayerInfoComponent> {
    public:
        void operator()(CharacterStateComponent& state, CharacterInfoComponent& characterInfo,
            PlayerInfoComponent& playerInfo);
    };

}


#endif // FUG_PLAYER_INPUT_VISITORS_HPP
