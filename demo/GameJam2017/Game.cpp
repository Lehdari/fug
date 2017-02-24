#include <SFML/System.hpp>
#include "GameJam2017/Game.hpp"
#include "Core/ResourceManager.hpp"
#include "Core/Scene.hpp"
#include "Logic/SfmlInputConfig.hpp"
#include "Logic/SfmlInputConfig_Init.hpp"
#include "Logic/TransformComponent.hpp"
#include "GameJam2017/PlayerInputVisitor.hpp"
#include "GameJam2017/PlayerComponent.hpp"
#include "GameJam2017/CharacterStateComponent.hpp"
#include "GameJam2017/CharacterInfoComponent.hpp"

#include <cstdint>

using namespace fgj;
using namespace fug;

Game::Game()
{
// Input mapping
    // <key, <player_id, action>>
    SfmlInputConfig_Init_Default inputMap = {
        SfmlInputConfig::InputMap{
            { sf::Keyboard::W, std::make_pair(0, Input::Up) },
            { sf::Keyboard::A, std::make_pair(0, Input::Left) },
            { sf::Keyboard::S, std::make_pair(0, Input::Down) },
            { sf::Keyboard::D, std::make_pair(0, Input::Right) },

            { sf::Keyboard::W, std::make_pair(1, Input::Up) },
            { sf::Keyboard::A, std::make_pair(1, Input::Left) },
            { sf::Keyboard::S, std::make_pair(1, Input::Down) },
            { sf::Keyboard::D, std::make_pair(1, Input::Right) },
        }
    };
    FUG_RESOURCE_MANAGER.addResourceInfo<SfmlInputConfig, SfmlInputConfig_Init_Default>(1,
        std::move(inputMap));

    //window.setFramerateLimit(60);
}

Game::~Game()
{
}

bool Game::loadLevel(std::string name)
{
    return true;
}

void Game::loop()
{
    EId nid[666] = {0};
    uint64_t i = 0;

    std::cerr << "adding character" << std::endl;
    nid[i++] = FUG_SCENE.addEntity();
    FUG_SCENE.addComponent(CharacterInfoComponent());
    FUG_SCENE.addComponent(PlayerComponent());
    FUG_SCENE.addComponent(CharacterStateComponent());

    PlayerInputVisitor playerInputVisitor;

    std::cout << "entering loop" << std::endl;

    float dt = 1.f/60.f;
    uint32_t velocityIterations = 6;
    uint32_t positionIterations = 2;
    while(true) {
        FUG_SCENE.accept(playerInputVisitor);
    }
}
