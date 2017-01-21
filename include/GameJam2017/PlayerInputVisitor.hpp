#ifndef FUG_PLAYER_INPUT_VISITOR_HPP
#define FUG_PLAYER_INPUT_VISITOR_HPP


#include "Core/Visitor.hpp"
#include "GameJam2017/CharacterStateComponent.hpp"
#include "GameJam2017/CharacterInfoComponent.hpp"
#include "GameJam2017/PlayerComponent.hpp"


namespace fug {


    class PlayerInputVisitor : public Visitor<PlayerInputVisitor,
        CharacterStateComponent, CharacterInfoComponent, PlayerComponent> {
    public:
        void operator()(CharacterStateComponent& state, CharacterInfoComponent& characterInfo,
            PlayerComponent& playerInfo);
    };

}


#endif // FUG_PLAYER_INPUT_VISITOR_HPP
