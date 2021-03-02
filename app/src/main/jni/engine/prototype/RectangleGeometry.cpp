// engine
#include "RectangleGeometry.hpp"

// style
#include <style/Guidelines.hpp>

RectangleGeometry::RectangleGeometry(const vec2& size)
    : Geometry()
    , m_size(size)
    , m_onUpdate()
{
    //
}

RectangleGeometry::RectangleGeometry()
    : RectangleGeometry(vec2())
{
    //
}

Geometry::size_type RectangleGeometry::points() const
{
    return 4;
}

vec2 RectangleGeometry::pointAt(size_type index) const
{

    switch (index) {
    case 0:
        return vec2(0.f, 0.f);
        break;
    case 1:
        return vec2(m_size.x, 0.f);
        break;
    case 2:
        return vec2(m_size.x, m_size.y);
        break;
    case 3:
        return vec2(0.f, m_size.y);
        break;
    default:
        return vec2(0.f, 0.f);
    }

    return vec2(0.f, 0.f);
}

RectangleGeometry::OnUpdateSignal& RectangleGeometry::onUpdate()
{
    return m_onUpdate;
}

void RectangleGeometry::resize(const vec2& size)
{
    m_size = size;
    m_onUpdate.emit();
}

const vec2& RectangleGeometry::size() const
{
    return m_size;
}
