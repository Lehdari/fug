//
// Created by Lehdari on 29.9.2018.
//

#include "Window.hpp"


Window::Window(const Window::Settings &settings) :
    _settings   (settings),
    _window     (_settings.videoMode, _settings.windowName)
{
    _window.setFramerateLimit(_settings.framerateLimit);
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

        render();

        _window.display();
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

void Window::render(void)
{
    //  Render OpenGL stuff here
}
