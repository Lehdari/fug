#include <Graphics/Canvas_SFML.hpp>
//#include <Core/Event.hpp>

#include <GL/glew.h>

using namespace fug;


Canvas_SFML::Canvas_SFML(void)
{
    // window settings
    sf::ContextSettings settings;
    settings.depthBits = 24;
    settings.stencilBits = 8;
    settings.antialiasingLevel = 4;
    settings.majorVersion = 3;
    settings.minorVersion = 3;

    _window.create(sf::VideoMode(1280, 720), "fug", sf::Style::Default, settings);
    _window.setFramerateLimit(60);
    
    // Load gl-functions (glLoadGen-header)
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        throw "Loading ogl extensions failed!";
    }
    
    glClearColor(0.f, 0.f, 0.f, 1.f);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);
}

Canvas_SFML::~Canvas_SFML()
{
    if (_window.isOpen()) _window.close();
}

bool Canvas_SFML::isOpen(void) {
    return _window.isOpen();
}

void Canvas_SFML::display(void) {
    _window.display();
}

void Canvas_SFML::close(void) {
    _window.close();
}

void Canvas_SFML::handleEvents(void)
{
    // Handle events from _window
    sf::Event event;
    while (_window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            // Close the window
            close();
        }
        else if (event.type == sf::Event::Resized) {
            // Adjust the viewport when the window is resized
            glViewport(0, 0, event.size.width, event.size.height);
        }
        else if (event.type == sf::Event::KeyPressed) {
            // Key pressed, fire core event
            FUG_EVENT_MANAGER.pushEvent(event, sf::Event::KeyPressed);
        }
        else if (event.type == sf::Event::KeyReleased) {
            // Key released, fire core event
            FUG_EVENT_MANAGER.pushEvent(event, sf::Event::KeyReleased);
        }
        else {
            // Unhandled event
        }
    }
}

sf::Window* Canvas_SFML::getWindow(void) {
    return &_window;
}
