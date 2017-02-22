#ifndef FUG_CORE_CANVAS_HPP
#define FUG_CORE_CANVAS_HPP


//#include <Core/EventBase.hpp>

#include <memory>


namespace fug {

    template<typename CanvasType_T>
    class Canvas {
    public:
        Canvas(void) {}
        ~Canvas(void) {}

        bool isOpen(void) {
            return static_cast<CanvasType_T*>(this)->isOpen();
        }

        void display(void) {
            static_cast<CanvasType_T*>(this)->display();
        }

        void close(void) {
            static_cast<CanvasType_T*>(this)->close();
        }

        void handleEvents(void) {
            return static_cast<CanvasType_T*>(this)->handleEvents();
        }
    };
}


#endif // FUG_CORE_CANVAS_HPP
