#include "FlappyCatWall.hpp"
#include <core/Log.hpp>
#include <physics/Collide.hpp>
#include <style/Guidelines.hpp>

FlappyCatWall::FlappyCatWall(const FlappyCatGameConstants& gameConstants)
    : FlappyCatStateNode<FlappyCatWall>(gameConstants)
    , mGapInterval(0.f)
    , mGapDisplacement(0.f)
    , mTopBlock()
    , mBottomBlock()
    , mWallState(WallState::Normal)
{
    //
}

void FlappyCatWall::setGapInterval(float interval)
{
    mGapInterval = interval;
    syncChildren();
}

void FlappyCatWall::setGapDisplacement(float displacement)
{
    mGapDisplacement = displacement;
    syncChildren();
}

bool FlappyCatWall::collideWithCircle(const Position& center, float radius)
{
    return Collide::circleRect(center, radius, mTopBlock)
        || Collide::circleRect(center, radius, mBottomBlock);
}

void FlappyCatWall::drawOn(const Window& window) const
{
    window.draw(mTopBlock);
    window.draw(mBottomBlock);
}

void FlappyCatWall::setColor(const Color& color)
{
    mTopBlock.setColor(color);
    mBottomBlock.setColor(color);
}

const Color& FlappyCatWall::color() const
{
    return mTopBlock.color();
}

void FlappyCatWall::syncChildren()
{
    float A1 = position().y();

    float A2 = A1 + size().y()
        - mGapInterval / 2.f
        - size().y() / 2.f
        - mGapDisplacement;

    float A3 = A2 + mGapInterval;

    float A4 = A3 + size().y() / 2.f
        + mGapDisplacement
        - mGapInterval / 2.f;

    // Need to deal with situation when all values are 0.f to make assert work
    //REQUIRE(TAG, ((A1 < A2) && (A2 < A3) && (A3 < A4)), "Vectors must not overlap");

    mBottomBlock.transformation().setPosition(Position(position().x(), A1));
    mBottomBlock.geometry().resize(Position(size().x(), (A2 - A1)));

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
