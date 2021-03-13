#include "View.hpp"

View::View()
    : Transformation()
    , m_size(0.f, 0.f)
    , m_scale(1.f, 1.f)
    , m_angle(0.f)
{
    //
}

void View::setPosition(const vec2& position)
{
    m_size = position;
}

const vec2& View::position() const
{
    return m_size;
}

void View::setScale(const vec2& factor)
{
    m_scale = factor;
}

const vec2& View::scale() const
{
    return m_scale;
}

void View::setRotation(float angle)
{
    m_angle = angle;
}

float View::rotation() const
{
    return m_angle;
}
