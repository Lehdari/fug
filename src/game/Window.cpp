//
// Created by Lehdari on 29.9.2018.
//

#include <game/Window.hpp>
#include <engine/LogicComponent.hpp>
#include <game/PhysicsComponent.hpp>
#include <game/EventHandlers.hpp>
#include <game/Logics.hpp>


Window::Window(const Window::Settings &settings) :
    _settings           (settings),
    _window             (_settings.videoMode, _settings.windowName),
    _playerId           (0),
    _ballId             (1),
    _spriteRenderer     (_window),
    _eventSystem        (_ecs),
    _collisionSystem    (_ecs, _eventSystem),
    _logicSystem        (_ecs)
{
    _window.setFramerateLimit(_settings.framerateLimit);

    _blockTexture.loadFromFile("../res/gfx/blocks.png");
    _ballTexture.loadFromFile("../res/gfx/ball.png");

    /* Player */
    _ecs.addComponent(_playerId, PhysicsComponent(
        vm::vec2f(400, 550), vm::vec2f(0.0, 0.0f),
        CollisionVolume(CollisionVolume::BOX, -32.0f, -16.0f, 32.0f, 16.0f)));
    _ecs.addComponent(_playerId, SpriteComponent(_blockTexture, 3, 64, 32));
    _ecs.getComponent<SpriteComponent>(_playerId)->sprite.setOrigin(32, 16);
    _ecs.addComponent(_playerId, LogicComponent());
    _ecs.getComponent<LogicComponent>(_playerId)->addLogic<Logic_Paddle>();

    /* Ball */
    _ecs.addComponent(_ballId, PhysicsComponent(
        vm::vec2f(400, 518), vm::vec2f(0.0f, 0.0f),
        CollisionVolume(CollisionVolume::CIRCLE, 16.0f)));
    _ecs.addComponent(_ballId, SpriteComponent(_ballTexture, 0, 32, 32));
    _ecs.getComponent<SpriteComponent>(_ballId)->sprite.setOrigin(16, 16);
    _ecs.addComponent(_ballId, EventComponent());
    _ecs.getComponent<EventComponent>(_ballId)->addHandler<EventHandler_Ball_CollisionEvent>();
    _ecs.getComponent<EventComponent>(_ballId)->addHandler<EventHandler_Ball_LaunchEvent>();
    _ecs.addComponent(_ballId, LogicComponent());
    _ecs.getComponent<LogicComponent>(_ballId)->addLogic<Logic_Ball>(_playerId);

    /* Walls */
    _ecs.addComponent(2, PhysicsComponent(
        vm::vec2f(-16, 300), vm::vec2f(0.0f, 0.0f),
        CollisionVolume(CollisionVolume::BOX, -16.0f, -300.0f, 16.0f, 300.0f)));
    _ecs.addComponent(3, PhysicsComponent(
        vm::vec2f(816, 300), vm::vec2f(0.0f, 0.0f),
        CollisionVolume(CollisionVolume::BOX, -16.0f, -300.0f, 16.0f, 300.0f)));
    _ecs.addComponent(4, PhysicsComponent(
        vm::vec2f(400, -16), vm::vec2f(0.0f, 0.0f),
        CollisionVolume(CollisionVolume::BOX, -400.0f, -16.0f, 400.0f, 16.0f)));
    _ecs.addComponent(5, PhysicsComponent(
        vm::vec2f(400, 616), vm::vec2f(0.0f, 0.0f),
        CollisionVolume(CollisionVolume::BOX, -400.0f, -16.0f, 400.0f, 16.0f)));

    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 5; ++j) {
            uint64_t id = i * 8 + j + 6;
            _ecs.addComponent(id, PhysicsComponent(
                vm::vec2f(176 + i * 64, 64 + j * 32), vm::vec2f(0.0f, 0.0f),
                CollisionVolume(CollisionVolume::BOX, -32.0f, -16.0f, 32.0f, 16.0f)));
            _ecs.addComponent(id, SpriteComponent(_blockTexture, (i ^ j) % 4, 64, 32));
            _ecs.getComponent<SpriteComponent>(id)->sprite.setOrigin(32, 16);

            _ecs.addComponent(id, EventComponent());
            _ecs.getComponent<EventComponent>(id)->addHandler<EventHandler_Block_CollisionEvent>();
        }
    }
}

void Window::loop(void)
{
    _window.setActive();
    while (_window.isOpen())
    {
        // Event processing
        sf::Event event;
        while (_window.pollEvent(event))
            handleEvents(event);

        runSystems();
        render();

        _window.display();
        _window.clear();
    }
}

void Window::handleEvents(sf::Event &event)
{
    switch (event.type) {
        case sf::Event::Closed:
            _window.close();
            break;

        case sf::Event::KeyPressed:
            switch (event.key.code) {
                case sf::Keyboard::Escape:
                    _window.close();
                    break;

                case sf::Keyboard::Space:
                    _eventSystem.sendEvent(_ballId, LaunchEvent());
            }
            break;

        default:
            break;
    }
}

void Window::runSystems(void)
{
    _ecs.runSystem(_physicsSystem);
    _ecs.runSystem(_spriteRenderer);
    _ecs.runSystem(_collisionSystem);
    _ecs.runSystem(_eventSystem);
    _ecs.runSystem(_logicSystem);

    _eventSystem.clear();
}

void Window::render(void)
{
    //  Render OpenGL stuff here
}
