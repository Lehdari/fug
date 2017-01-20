#ifndef FUG_PLAYER_INPUT_VISITORS_HPP
#define FUG_PLAYER_INPUT_VISITORS_HPP


#include "Core/Visitor.hpp"
#include "GameJam2017/CharacterStateComponent.hpp"
#include "GameJam2017/CharacterInfoComponent.hpp"


namespace fug {


    class PlayerInputVisitor : public Visitor<PlayerInputVisitor,
        CharacterStateComponent, CharacterInfoComponent> {
    public:
        void operator()(CharacterStateComponent& state, CharacterInfoComponent& info);
    };

}


#endif // FUG_PLAYER_INPUT_VISITORS_HPP
