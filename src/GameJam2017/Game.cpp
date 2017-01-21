#include <SFML/System.hpp>
#include "GameJam2017/Game.hpp"
#include "Core/ResourceManager.hpp"
#include "Core/Scene.hpp"
#include "Logic/SfmlInputConfig.hpp"
#include "Logic/SfmlInputConfig_Init.hpp"
#include "GameJam2017/PlayerInputVisitor.hpp"
#include "GameJam2017/PlayerInfoComponent.hpp"
#include "GameJam2017/CharacterStateComponent.hpp"
#include "GameJam2017/CharacterInfoComponent.hpp"

using namespace fgj;
using namespace fug;

Game::Game() {
// Input mapping
    // <key, <player_id, action>>
    SfmlInputConfig_Init_Default inputMap = {
        SfmlInputConfig::InputMap{
            { sf::Keyboard::W, std::make_pair(1, Input::Up) },
            { sf::Keyboard::A, std::make_pair(1, Input::Left) },
            { sf::Keyboard::S, std::make_pair(1, Input::Down) },
            { sf::Keyboard::D, std::make_pair(1, Input::Right) },

            { sf::Keyboard::W, std::make_pair(2, Input::Up) },
            { sf::Keyboard::A, std::make_pair(2, Input::Left) },
            { sf::Keyboard::S, std::make_pair(2, Input::Down) },
            { sf::Keyboard::D, std::make_pair(2, Input::Right) },
        }
    };
    FUG_RESOURCE_MANAGER.addResourceInfo<SfmlInputConfig, SfmlInputConfig_Init_Default>(1, std::move(inputMap));

    //window.setFramerateLimit(60);
}

Game::~Game() {
}

void Game::loop() {
    EId nid[666] = {0};
    uint64_t i = 0;

    nid[i++] = FUG_SCENE.addEntity(CharacterInfoComponent(), PlayerInfoComponent(),
        CharacterStateComponent());

    PlayerInputVisitor playerInputVisitor;

    while(true) {
        FUG_SCENE.accept(playerInputVisitor);
    }   
}
