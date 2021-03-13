#include "CircleGeometry.hpp"
#include <cmath>

CircleGeometry::CircleGeometry(float radius, std::size_t resolution)
    : Geometry()
    , m_radius(radius)
    , m_resolution(resolution)
    , m_origin(0.f, 0.f)
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

vec2 CircleGeometry::pointAt(size_type index) const
{
    constexpr float pi = 3.141592654f;

    float angle = index * 2.f * pi / m_resolution - pi / 2.f;
    float x = std::cos(angle) * m_radius;
    float y = std::sin(angle) * m_radius;

    return vec2(x, y);
}

void CircleGeometry::setOrigin(const vec2& position)
{
    REQUIRE(TAG, false, "origin is not supported yet");
    m_origin = position;
    m_onUpdate.emit();
}

const vec2& CircleGeometry::origin() const
{
    return m_origin;
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
