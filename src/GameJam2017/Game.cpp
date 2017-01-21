#include <SFML/System.hpp>
#include "GameJam2017/Game.hpp"
#include "Core/ResourceManager.hpp"
#include "Core/Scene.hpp"
#include "Logic/SfmlInputConfig.hpp"
#include "Logic/SfmlInputConfig_Init.hpp"
#include "Logic/Box2dWorld.hpp"
#include "Logic/Box2dWorld_Init.hpp"
#include "Logic/createPhysicsBox.hpp"
#include "Logic/Box2dTransformVisitor.hpp"
#include "Logic/TransformComponent.hpp"
#include "GameJam2017/PlayerInputVisitor.hpp"
#include "GameJam2017/PlayerComponent.hpp"
#include "GameJam2017/CharacterStateComponent.hpp"
#include "GameJam2017/CharacterInfoComponent.hpp"

#include <iostream> // TEMP
#include <cstdint>

using namespace fgj;
using namespace fug;

Game::Game() :
    worldRes()
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
    FUG_RESOURCE_MANAGER.addResourceInfo<Box2dWorld, Box2dWorld_Init_Default>(2,
        Box2dWorld_Init_Default(b2Vec2(0, -8.f)));
    worldRes = FUG_RESOURCE_MANAGER.getResource<Box2dWorld>(2);

    return true;
}

void Game::loop()
{
    EId nid[666] = {0};
    uint64_t i = 0;

    std::cerr << "adding phys box" << std::endl;
    nid[i++] = FUG_SCENE.addEntity(TransformComponent(),
        createPhysicsBox(b2_dynamicBody, b2Vec2(0, 3), b2Vec2(0.1f, 0.1f), 1.f, 0.01f));

    std::cerr << "adding character" << std::endl;
    nid[i++] = FUG_SCENE.addEntity(CharacterInfoComponent(), PlayerComponent(),
        CharacterStateComponent());

    PlayerInputVisitor playerInputVisitor;
    Box2dTransformVisitor physTransformVisitor;

    std::cout << "entering loop" << std::endl;

    float dt = 1.f/60.f;
    uint32_t velocityIterations = 6;
    uint32_t positionIterations = 2;
    //while(true) {
        worldRes->world->Step(dt, velocityIterations, positionIterations);
        FUG_SCENE.accept(physTransformVisitor);
        FUG_SCENE.accept(playerInputVisitor);
    //}   
}
