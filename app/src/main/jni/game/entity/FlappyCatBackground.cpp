#include "FlappyCatBackground.hpp"

FlappyCatBackground::FlappyCatBackground(const FlappyCatGameConstants& gameConstants)
    : FlappyCatStateNode<FlappyCatBackground>(gameConstants)
    , m_background()
{
    //
}

void FlappyCatBackground::drawOn(const Window& window) const
{
    m_background.render().drawOn(window, window.view());
}

void FlappyCatBackground::setColor(const Color& color)
{
    m_background.setColor(color);
}

void FlappyCatBackground::syncChildren()
{
    m_background.transformation().setPosition(position());
    m_background.geometry().resize(size());
}
