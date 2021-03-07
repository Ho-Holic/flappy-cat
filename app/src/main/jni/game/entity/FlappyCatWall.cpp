#include "FlappyCatWall.hpp"
#include <core/Log.hpp>
#include <physics/Collide.hpp>
#include <style/Guidelines.hpp>

FlappyCatWall::FlappyCatWall(const FlappyCatGameConstants& gameConstants)
    : FlappyCatStateNode<FlappyCatWall>(gameConstants)
    , m_gapInterval(0.f)
    , m_gapDisplacement(0.f)
    , m_topBlock()
    , m_bottomBlock()
    , m_wallState(WallState::Normal)
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

bool FlappyCatWall::collideWithCircle(const vec2& center, float radius)
{
    return Collide::circleRect(center, radius, m_topBlock)
        || Collide::circleRect(center, radius, m_bottomBlock);
}

void FlappyCatWall::drawOn(const Window& window) const
{
    m_topBlock.render().drawOn(window, window.view());
    m_bottomBlock.render().drawOn(window, window.view());
}

void FlappyCatWall::setColor(const Color& color)
{
    m_topBlock.setColor(color);
    m_bottomBlock.setColor(color);
}

const Color& FlappyCatWall::color() const
{
    return m_topBlock.color();
}

void FlappyCatWall::syncChildren()
{
    float A1 = position().y;

    float A2 = A1 + size().y
        - m_gapInterval / 2.f
        - size().y / 2.f
        - m_gapDisplacement;

    float A3 = A2 + m_gapInterval;

    float A4 = A3 + size().y / 2.f
        + m_gapDisplacement
        - m_gapInterval / 2.f;

    // Need to deal with situation when all values are 0.f to make assert work
    //REQUIRE(TAG, ((A1 < A2) && (A2 < A3) && (A3 < A4)), "Vectors must not overlap");

    m_bottomBlock.transformation().setPosition(vec2(position().x, A1));
    m_bottomBlock.geometry().resize(vec2(size().x, (A2 - A1)));

    m_topBlock.transformation().setPosition(vec2(position().x, A3));
    m_topBlock.geometry().resize(vec2(size().x, (A4 - A3)));
}

void FlappyCatWall::activateWall()
{
    m_wallState = WallState::Activated;
}

bool FlappyCatWall::isActivated() const
{
    return m_wallState == WallState::Activated;
}
