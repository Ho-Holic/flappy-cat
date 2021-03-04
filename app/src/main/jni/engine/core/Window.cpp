#include "Window.hpp"

Window::Window()
    : m_view()
{
    //
}

const View& Window::view() const
{
    return m_view;
}

View& Window::view()
{
    return m_view;
}
