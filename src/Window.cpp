//
// Created by Lehdari on 29.9.2018.
//

#include "Window.hpp"
#include "PhysicsComponent.hpp"


Window::Window(const Window::Settings &settings) :
    _settings       (settings),
    _window         (_settings.videoMode, _settings.windowName),
    _playerId       (0),
    _ballId         (1),
    _spriteRenderer (_window)
{
    _window.setFramerateLimit(_settings.framerateLimit);

    _blockTexture.loadFromFile("../res/gfx/blocks.png");
    _ballTexture.loadFromFile("../res/gfx/ball.png");

    /* Player */
    _ecs.addComponent(_playerId, PhysicsComponent(mm::Vec2f(400, 550),
                                                  mm::Vec2f(-0.5, 0.0f)));
    _ecs.addComponent(_playerId, SpriteComponent(_blockTexture, 3, 64, 32));

    /* Ball */
    _ecs.addComponent(_ballId, PhysicsComponent(mm::Vec2f(400, 300),
                                                mm::Vec2f(0.7f, 0.7f)));
    _ecs.addComponent(_ballId, SpriteComponent(_ballTexture, 0, 32, 32));

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
}

void Window::render(void)
{
    //  Render OpenGL stuff here
}
