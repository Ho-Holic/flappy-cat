// game
#include "FlappyCatSpike.hpp"

FlappyCatSpike::FlappyCatSpike(const FlappyCatGameConstants& gameConstants)
    : FlappyCatEntity(gameConstants)
    , mSpike()
{
    //
}

void FlappyCatSpike::drawOn(const Window& window) const
{

    window.draw(mSpike);
}

void FlappyCatSpike::setColor(const Color& color)
{

    mSpike.setColor(color);
}

void FlappyCatSpike::syncChildren()
{

    mSpike.transformation().setPosition(position());
    mSpike.geometry().resize(size());
}
