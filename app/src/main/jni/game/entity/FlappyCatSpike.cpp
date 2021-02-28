#include "FlappyCatSpike.hpp"

FlappyCatSpike::FlappyCatSpike(const FlappyCatGameConstants& gameConstants)
    : FlappyCatStateNode<FlappyCatSpike>(gameConstants)
    , m_spike()
{
    //
}

void FlappyCatSpike::drawOn(const Window& window) const
{
    window.draw(m_spike);
}

void FlappyCatSpike::setColor(const Color& color)
{
    m_spike.setColor(color);
}

void FlappyCatSpike::syncChildren()
{
    m_spike.transformation().setPosition(position());
    m_spike.geometry().resize(size());
}
