// engine
#include "View.hpp"

View::View()
    : Transformation()
    , m_origin(0.f, 0.f)
    , m_size(0.f, 0.f)
    , m_scale(1.f, 1.f)
    , m_angle(0.f)
{
    //
}

void View::setOrigin(const Position& origin)
{

    m_origin = origin;
}

const Position& View::origin() const
{

    return m_origin;
}

void View::setPosition(const Position& position)
{

    m_size = position;
}

const Position& View::position() const
{

    return m_size;
}

void View::setScale(const Position& factor)
{

    m_scale = factor;
}

const Position& View::scale() const
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
