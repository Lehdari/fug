#ifndef FUG_CORE_CANVAS_HPP
#define FUG_CORE_CANVAS_HPP

#include <memory>


namespace fug {

    template <typename CanvasType_T>
    class Canvas {

    public:
        bool isOpen(void);
        void display(void);
        void close(void);
        void handleEvents(void);
    };
}

#endif // FUG_CORE_CANVAS_HPP
