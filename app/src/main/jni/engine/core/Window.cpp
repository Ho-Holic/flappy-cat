// engine
#include "Window.hpp"

Window::Window()
    : mView()
{
    //
}

const View& Window::view() const
{

    return mView;
}

View& Window::view()
{

    return mView;
}
