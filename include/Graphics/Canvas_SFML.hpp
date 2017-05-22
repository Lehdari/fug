#ifndef FUG_GRAPHICS_CANVAS_SFML_HPP
#define FUG_GRAPHICS_CANVAS_SFML_HPP


#include <Graphics/Canvas.hpp>
#include <SFML/Window.hpp>

#include "Core/EventManager.hpp"


namespace fug {

    class Canvas_SFML : public Canvas<Canvas_SFML> {
    public:
        Canvas_SFML(void);
        ~Canvas_SFML(void);

        bool isOpen(void);
        void display(void);
        void close(void);
        void handleEvents(void);

        sf::Window* getWindow(void);

    private:
        sf::Window _window;
    };
}


#endif // FUG_COREEXTENSIONS_CANVAS_SFML_HPP
