#include "FlappyCatViewLimit.hpp"

FlappyCatViewLimit::FlappyCatViewLimit(const FlappyCatGameConstants& gameConstants)
    : FlappyCatStateNode<FlappyCatViewLimit>(gameConstants)
    , mTop()
    , mTopRight()
    , m_right()
    , m_bottomRight()
    , m_bottom()
    , m_bottomLeft()
    , m_left()
    , mTopLeft()
{
    //
}

void FlappyCatViewLimit::syncChildren()
{
    const Position& position = this->position();
    const Position& size = this->size();

    // move
    mTop.transformation().setPosition(position + Position(0.f, size.y()));
    mTopRight.transformation().setPosition(position + Position(size.x(), size.y()));
    m_right.transformation().setPosition(position + Position(size.x(), 0.f));
    m_bottomRight.transformation().setPosition(position + Position(size.x(), -size.y()));
    m_bottom.transformation().setPosition(position + Position(0.f, -size.y()));
    m_bottomLeft.transformation().setPosition(position + Position(-size.x(), -size.y()));
    m_left.transformation().setPosition(position + Position(-size.x(), 0.f));
    mTopLeft.transformation().setPosition(position + Position(-size.x(), size.y()));

    // resize
    mTop.geometry().resize(size);
    mTopRight.geometry().resize(size);
    m_right.geometry().resize(size);
    m_bottomRight.geometry().resize(size);
    m_bottom.geometry().resize(size);
    m_bottomLeft.geometry().resize(size);
    m_left.geometry().resize(size);
    mTopLeft.geometry().resize(size);
}

void FlappyCatViewLimit::drawOn(const Window& window) const
{
    window.draw(mTop);
    window.draw(mTopRight);
    window.draw(m_right);
    window.draw(m_bottomRight);
    window.draw(m_bottom);
    window.draw(m_bottomLeft);
    window.draw(m_left);
    window.draw(mTopLeft);
}
