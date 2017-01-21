#ifndef FUG_GRAPHICS_CANVAS_SFML_HPP
#define FUG_GRAPHICS_CANVAS_SFML_HPP


#include "glLoadGen/gl_core_3_3.h"
#include <Graphics/Canvas.hpp>
#include <SFML/Window.hpp>


namespace fug {

    class Canvas_SFML : public Canvas<Canvas_SFML> {
    public:
        Canvas_SFML(void);
        ~Canvas_SFML(void) {}

        bool isOpen(void);
        void display(void);
        void close(void);
        //std::shared_ptr<EventBase> pollEvent(void);

        sf::Window* getWindow(void);

    private:
        sf::Window window_;
    };
}


#endif // FUG_COREEXTENSIONS_CANVAS_SFML_HPP
