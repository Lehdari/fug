//
// Created by Lehdari on 29.9.2018.
//

#include "Window.hpp"
#include "PhysicsComponent.hpp"
#include "EventHandlers.hpp"


Window::Window(const Window::Settings &settings) :
    _settings           (settings),
    _window             (_settings.videoMode, _settings.windowName),
    _playerId           (0),
    _ballId             (1),
    _spriteRenderer     (_window),
    _eventSystem        (_ecs),
    _collisionSystem    (_ecs, _eventSystem)
{
    _window.setFramerateLimit(_settings.framerateLimit);

    _blockTexture.loadFromFile("../res/gfx/blocks.png");
    _ballTexture.loadFromFile("../res/gfx/ball.png");

    /* Player */
    _ecs.addComponent(_playerId, PhysicsComponent(
        mm::Vec2f(450, 550), mm::Vec2f(0.5, 0.0f),
        CollisionVolume(CollisionVolume::BOX, -32.0f, -16.0f, 32.0f, 16.0f)));
    _ecs.addComponent(_playerId, SpriteComponent(_blockTexture, 3, 64, 32));
    _ecs.getComponent<SpriteComponent>(_playerId)->sprite.setOrigin(32, 16);

    /* Ball */
    _ecs.addComponent(_ballId, PhysicsComponent(
        mm::Vec2f(400, 400), mm::Vec2f(-0.5f, 2.0f),
        CollisionVolume(CollisionVolume::CIRCLE, 16.0f)));
    _ecs.addComponent(_ballId, SpriteComponent(_ballTexture, 0, 32, 32));
    _ecs.getComponent<SpriteComponent>(_ballId)->sprite.setOrigin(16, 16);

    _ecs.addComponent(_ballId, EventComponent());
    _ecs.getComponent<EventComponent>(_ballId)->addHandler<EventHandler_Ball_CollisionEvent>();

    /* Walls */
    _ecs.addComponent(2, PhysicsComponent(
        mm::Vec2f(-16, 300), mm::Vec2f(0.0f, 0.0f),
        CollisionVolume(CollisionVolume::BOX, -16.0f, -300.0f, 16.0f, 300.0f)));
    _ecs.addComponent(3, PhysicsComponent(
        mm::Vec2f(816, 300), mm::Vec2f(0.0f, 0.0f),
        CollisionVolume(CollisionVolume::BOX, -16.0f, -300.0f, 16.0f, 300.0f)));
    _ecs.addComponent(4, PhysicsComponent(
        mm::Vec2f(400, -16), mm::Vec2f(0.0f, 0.0f),
        CollisionVolume(CollisionVolume::BOX, -400.0f, -16.0f, 400.0f, 16.0f)));
    _ecs.addComponent(5, PhysicsComponent(
        mm::Vec2f(400, 616), mm::Vec2f(0.0f, 0.0f),
        CollisionVolume(CollisionVolume::BOX, -400.0f, -16.0f, 400.0f, 16.0f)));

    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 5; ++j) {
            uint64_t id = i * 8 + j + 6;
            _ecs.addComponent(id, PhysicsComponent(
                mm::Vec2f(176 + i * 64, 64 + j * 32), mm::Vec2f(0.0f, 0.0f),
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

    _eventSystem.clear();
}

void Window::render(void)
{
    //  Render OpenGL stuff here
}
