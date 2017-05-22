
template <typename CanvasType_T>
bool Canvas<CanvasType_T>::isOpen(void)
{
    return static_cast<CanvasType_T*>(this)->isOpen();
}

template <typename CanvasType_T>
void Canvas<CanvasType_T>::display(void)
{
    static_cast<CanvasType_T*>(this)->display();
}

template <typename CanvasType_T>
void Canvas<CanvasType_T>::close(void)
{
    static_cast<CanvasType_T*>(this)->close();
}

template <typename CanvasType_T>
void Canvas<CanvasType_T>::handleEvents(void)
{
    static_cast<CanvasType_T*>(this)->handleEvents();
}
