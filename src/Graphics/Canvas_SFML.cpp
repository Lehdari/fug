#include <Graphics/Canvas_SFML.hpp>
//#include <Core/Event.hpp>


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

    window_.create(sf::VideoMode(1280, 720), "fug", sf::Style::Default, settings);
    window_.setFramerateLimit(60);
    
    // Load gl-functions (glLoadGen-header)
    if (ogl_LoadFunctions() == ogl_LOAD_FAILED) {
        throw "Loading ogl extensions failed!";
    }
    
}

bool Canvas_SFML::isOpen(void) {
    return window_.isOpen();
}

void Canvas_SFML::display(void) {
    window_.display();
}

void Canvas_SFML::close(void) {
    window_.close();
}

/*std::shared_ptr<EventBase> Cucca::Canvas_SFML::pollEvent(void) {
    sf::Event event;
    if (window_.pollEvent(event))
        return std::shared_ptr<EventBase>(new Event<sf::Event>(event));
    else
        return std::shared_ptr<EventBase>(nullptr);
}*/

sf::Window* Canvas_SFML::getWindow(void) {
    return &window_;
}
