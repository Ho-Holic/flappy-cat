
// game
#include "FlappyCatBackground.hpp"

FlappyCatBackground::FlappyCatBackground(const FlappyCatGameConstants& gameConstants)
    : FlappyCatEntity(gameConstants)
    , mBackground()
    , mResetModifier([](entity_type&) {})
{
    //
}

void FlappyCatBackground::drawOn(const Window& window) const
{

    window.draw(mBackground);
}

void FlappyCatBackground::setResetModifier(const FlappyCatBackground::modifier_type& modifier)
{

    mResetModifier = modifier;
}

void FlappyCatBackground::reset()
{

    mResetModifier(*this);
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
