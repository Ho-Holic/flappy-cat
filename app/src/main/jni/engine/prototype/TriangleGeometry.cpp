
// engine
#include "TriangleGeometry.hpp"

TriangleGeometry::TriangleGeometry(const vec2& size)
    : Geometry()
    , m_size(size)
    , m_onUpdate()
{
    //
}

TriangleGeometry::TriangleGeometry()
    : TriangleGeometry(vec2())
{
    //
}

TriangleGeometry::OnUpdateSignal& TriangleGeometry::onUpdate()
{
    return m_onUpdate;
}

void TriangleGeometry::resize(const vec2& size)
{
    m_size = size;
    m_onUpdate.emit();
}

const vec2& TriangleGeometry::size() const
{

    return m_size;
}

Geometry::size_type TriangleGeometry::points() const
{

    return 3;
}

vec2 TriangleGeometry::pointAt(Geometry::size_type index) const
{

    switch (index) {
    case 0:
        return vec2(0.f, 0.f);
        break;
    case 1:
        return vec2(m_size.x, 0.f);
        break;
    case 2:
        return vec2(0.f, m_size.y);
        break;
    default:
        return vec2(0.f, 0.f);
    }

    return vec2(0.f, 0.f);
}
