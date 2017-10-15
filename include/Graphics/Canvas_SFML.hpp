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

        void setCursorVisible(bool);
        void setCursorMovable(bool);
        void setCursorPosition(sf::Vector2i);
        void setCursorLock(bool);

    private:
        sf::Window _window;

        bool _cursor_movable;
        sf::Vector2i _cursor_pos;
    };
}


#endif // FUG_COREEXTENSIONS_CANVAS_SFML_HPP
