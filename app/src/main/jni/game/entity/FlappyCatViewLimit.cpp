#include "FlappyCatViewLimit.hpp"

FlappyCatViewLimit::FlappyCatViewLimit(const FlappyCatGameConstants& gameConstants)
    : FlappyCatStateNode<FlappyCatViewLimit>(gameConstants)
    , mTop()
    , mTopRight()
    , mRight()
    , m_bottomRight()
    , m_bottom()
    , m_bottomLeft()
    , mLeft()
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
    mRight.transformation().setPosition(position + Position(size.x(), 0.f));
    m_bottomRight.transformation().setPosition(position + Position(size.x(), -size.y()));
    m_bottom.transformation().setPosition(position + Position(0.f, -size.y()));
    m_bottomLeft.transformation().setPosition(position + Position(-size.x(), -size.y()));
    mLeft.transformation().setPosition(position + Position(-size.x(), 0.f));
    mTopLeft.transformation().setPosition(position + Position(-size.x(), size.y()));

    // resize
    mTop.geometry().resize(size);
    mTopRight.geometry().resize(size);
    mRight.geometry().resize(size);
    m_bottomRight.geometry().resize(size);
    m_bottom.geometry().resize(size);
    m_bottomLeft.geometry().resize(size);
    mLeft.geometry().resize(size);
    mTopLeft.geometry().resize(size);
}

void FlappyCatViewLimit::drawOn(const Window& window) const
{
    window.draw(mTop);
    window.draw(mTopRight);
    window.draw(mRight);
    window.draw(m_bottomRight);
    window.draw(m_bottom);
    window.draw(m_bottomLeft);
    window.draw(mLeft);
    window.draw(mTopLeft);
}
