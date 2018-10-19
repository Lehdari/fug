#include "Window.hpp"


int main(void) {
    Window window(Window::Settings("ECSTestGame"));

    window.loop();

    return 0;
}
