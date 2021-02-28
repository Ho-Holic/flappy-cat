
// engine
#include "CircleGeometry.hpp"

// stl
#include <cmath>

CircleGeometry::CircleGeometry(float radius, std::size_t resolution)
    : Geometry()
    , m_radius(radius)
    , m_resolution(resolution)
    , m_onUpdate()
{
    //
}

CircleGeometry::CircleGeometry()
    : CircleGeometry(1.f, 32u)
{
    //
}

Geometry::size_type CircleGeometry::points() const
{

    return m_resolution;
}

Position CircleGeometry::pointAt(size_type index) const
{

    constexpr float pi = 3.141592654f;

    float angle = index * 2.f * pi / m_resolution - pi / 2.f;
    float x = std::cos(angle) * m_radius;
    float y = std::sin(angle) * m_radius;

    return Position(m_radius + x, m_radius + y);
}

CircleGeometry::OnUpdateSignal& CircleGeometry::onUpdate()
{

    return m_onUpdate;
}

void CircleGeometry::setResolution(std::size_t resolution)
{

    m_resolution = resolution;
    m_onUpdate.emit();
}

void CircleGeometry::setRadius(float radius)
{

    m_radius = radius;
    m_onUpdate.emit();
}

float CircleGeometry::radius() const
{

    return m_radius;
}
