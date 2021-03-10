#include "FlappyCatBackground.hpp"

FlappyCatBackground::FlappyCatBackground(const FlappyCatGameConstants& gameConstants)
    : FlappyCatStateNode<FlappyCatBackground>(gameConstants)
    , m_background()
{
    //
}

void FlappyCatBackground::drawOn(const Window& window, const RenderContext& renderContext) const
{
    m_background.render().drawOn(window, renderContext);
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
