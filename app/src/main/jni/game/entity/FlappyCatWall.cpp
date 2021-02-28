#include "FlappyCatWall.hpp"
#include <core/Log.hpp>
#include <physics/Collide.hpp>
#include <style/Guidelines.hpp>

FlappyCatWall::FlappyCatWall(const FlappyCatGameConstants& gameConstants)
    : FlappyCatStateNode<FlappyCatWall>(gameConstants)
    , m_gapInterval(0.f)
    , m_gapDisplacement(0.f)
    , mTopBlock()
    , m_bottomBlock()
    , mWallState(WallState::Normal)
{
    //
}

void FlappyCatWall::setGapInterval(float interval)
{
    m_gapInterval = interval;
    syncChildren();
}

void FlappyCatWall::setGapDisplacement(float displacement)
{
    m_gapDisplacement = displacement;
    syncChildren();
}

bool FlappyCatWall::collideWithCircle(const Position& center, float radius)
{
    return Collide::circleRect(center, radius, mTopBlock)
        || Collide::circleRect(center, radius, m_bottomBlock);
}

void FlappyCatWall::drawOn(const Window& window) const
{
    window.draw(mTopBlock);
    window.draw(m_bottomBlock);
}

void FlappyCatWall::setColor(const Color& color)
{
    mTopBlock.setColor(color);
    m_bottomBlock.setColor(color);
}

const Color& FlappyCatWall::color() const
{
    return mTopBlock.color();
}

void FlappyCatWall::syncChildren()
{
    float A1 = position().y();

    float A2 = A1 + size().y()
        - m_gapInterval / 2.f
        - size().y() / 2.f
        - m_gapDisplacement;

    float A3 = A2 + m_gapInterval;

    float A4 = A3 + size().y() / 2.f
        + m_gapDisplacement
        - m_gapInterval / 2.f;

    // Need to deal with situation when all values are 0.f to make assert work
    //REQUIRE(TAG, ((A1 < A2) && (A2 < A3) && (A3 < A4)), "Vectors must not overlap");

    m_bottomBlock.transformation().setPosition(Position(position().x(), A1));
    m_bottomBlock.geometry().resize(Position(size().x(), (A2 - A1)));

    mTopBlock.transformation().setPosition(Position(position().x(), A3));
    mTopBlock.geometry().resize(Position(size().x(), (A4 - A3)));
}

void FlappyCatWall::activateWall()
{
    mWallState = WallState::Activated;
}

bool FlappyCatWall::isActivated() const
{
    return mWallState == WallState::Activated;
}
