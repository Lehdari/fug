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

        /*std::shared_ptr<EventBase> pollEvent(void) {
            return static_cast<CanvasType_T*>(this)->pollEvent();
        }*/
    };
}


#endif // FUG_CORE_CANVAS_HPP
