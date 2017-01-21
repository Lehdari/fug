#include "Core/ResourceManager.hpp"
#include "Core/ResourcePointer.hpp"
#include "GameJam2017/PlayerInputVisitor.hpp"
#include "GameJam2017/constants.hpp"
#include "Logic/SfmlInputConfig.hpp"


using namespace fug;

void PlayerInputVisitor::operator()(CharacterStateComponent& state,
    CharacterInfoComponent& characterInfo, PlayerComponent& player)
{
    auto inputConfig = FUG_RESOURCE_MANAGER.getResource<SfmlInputConfig>(1);
    auto& inputMap = inputConfig->inputMap;

    // Iteroi eventit läpi
    /*
    if(inputMap.count(event.x.key.code) > 0) {
        auto playerAndAction = inputMap[event.x.key.code];
        if(!playerAndAction.first = player.playerId) {
            continue
        }
        bool keyPressed = (event.x.type == sf::Event::KeyPressed);
        switch(playerAndAction.second) {
            Input::Up:
                state.moveUp = keyPressed;
                state.moveDown = false;
                break;

            Input::Down:
                state.moveUp = false;
                state.moveDown = keyPressed;
                break;

            Input::Left:
                state.moveLeft = keyPressed;
                state.moveRight = false;
                break;

            Input::Right:
                state.moveLeft = false;
                state.moveRight = keyPressed;
                break;

            Input::Shoot:
                // Ammu shootevent
                break;
        }
    }
    */
}
