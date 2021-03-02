#include "FlappyCatViewLimit.hpp"

FlappyCatViewLimit::FlappyCatViewLimit(const FlappyCatGameConstants& gameConstants)
    : FlappyCatStateNode<FlappyCatViewLimit>(gameConstants)
    , m_top()
    , m_topRight()
    , m_right()
    , m_bottomRight()
    , m_bottom()
    , m_bottomLeft()
    , m_left()
    , m_topLeft()
{
    //
}

void FlappyCatViewLimit::syncChildren()
{
    const vec2& position = this->position();
    const vec2& size = this->size();

    // move
    m_top.transformation().setPosition(position + vec2(0.f, size.y));
    m_topRight.transformation().setPosition(position + vec2(size.x, size.y));
    m_right.transformation().setPosition(position + vec2(size.x, 0.f));
    m_bottomRight.transformation().setPosition(position + vec2(size.x, -size.y));
    m_bottom.transformation().setPosition(position + vec2(0.f, -size.y));
    m_bottomLeft.transformation().setPosition(position + vec2(-size.x, -size.y));
    m_left.transformation().setPosition(position + vec2(-size.x, 0.f));
    m_topLeft.transformation().setPosition(position + vec2(-size.x, size.y));

    // resize
    m_top.geometry().resize(size);
    m_topRight.geometry().resize(size);
    m_right.geometry().resize(size);
    m_bottomRight.geometry().resize(size);
    m_bottom.geometry().resize(size);
    m_bottomLeft.geometry().resize(size);
    m_left.geometry().resize(size);
    m_topLeft.geometry().resize(size);
}

void FlappyCatViewLimit::drawOn(const Window& window) const
{
    window.draw(m_top);
    window.draw(m_topRight);
    window.draw(m_right);
    window.draw(m_bottomRight);
    window.draw(m_bottom);
    window.draw(m_bottomLeft);
    window.draw(m_left);
    window.draw(m_topLeft);
}
