#include "FlappyCatBackground.hpp"

FlappyCatBackground::FlappyCatBackground(const FlappyCatGameConstants& gameConstants)
    : FlappyCatStateNode<FlappyCatBackground>(gameConstants)
    , mBackground()
{
    //
}

void FlappyCatBackground::drawOn(const Window& window) const
{
    window.draw(mBackground);
}

void FlappyCatBackground::setColor(const Color& color)
{
    mBackground.setColor(color);
}

void FlappyCatBackground::syncChildren()
{
    mBackground.transformation().setPosition(position());
    mBackground.geometry().resize(size());
}
