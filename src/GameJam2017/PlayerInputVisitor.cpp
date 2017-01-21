#include "Core/ResourceManager.hpp"
#include "GameJam2017/PlayerInputVisitor.hpp"
#include "GameJam2017/CharacterStateComponent.hpp"
#include "GameJam2017/CharacterInfoComponent.hpp"
#include "GameJam2017/PlayerComponent.hpp"
#include "GameJam2017/constants.hpp"
#include "Logic/SfmlInputConfig.hpp"

#include <iostream>

using namespace fug;

void PlayerInputVisitor::operator()(CharacterStateComponent& state,
    CharacterInfoComponent& characterInfo, PlayerComponent& player)
{
    auto inputConfig = FUG_RESOURCE_MANAGER.getResource<SfmlInputConfig>(1);
    auto& inputMap = inputConfig->inputMap;

    std::cerr << "penis" << std::endl;

    /*
    // Iteroi eventit läpi
    if(inputMap.count(event.x.key.code) > 0) {
        auto playerAndAction = inputMap[event.x.key.code];
        if(!playerAndAction.first = player.playerId) {
            continue
        }
        bool keyPressed = (event.x.type == sf::Event::KeyPressed);
        Vector3f dir(0.f, 0.f, 0.f);
        switch(playerAndAction.second) {
            Input::Up:
                dir += keyPressed ? Vector3f(0, 1.f, 0) : 0;
                break;

            Input::Down:
                dir += keyPressed ? Vector3f(0, -1.f, 0) : 0;
                break;

            Input::Left:
                dir += keyPressed ? Vector3f(-1.f, 0, 0) : 0;
                break;

            Input::Right:
                dir += keyPressed ? Vector3f(1.f, 0, 0) : 0;
                break;

            Input::Shoot:
                // Ammu shootevent
                break;
        }
        state.movementDir = dir.normalized();
    }
    */
}
