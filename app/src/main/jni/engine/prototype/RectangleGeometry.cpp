// engine
#include "RectangleGeometry.hpp"

// style
#include <style/Guidelines.hpp>

RectangleGeometry::RectangleGeometry(const Position& size)
    : Geometry()
    , m_size(size)
    , m_onUpdate()
{
    //
}

RectangleGeometry::RectangleGeometry()
    : RectangleGeometry(Position())
{
    //
}

Geometry::size_type RectangleGeometry::points() const
{
    return 4;
}

Position RectangleGeometry::pointAt(size_type index) const
{

    switch (index) {
    case 0:
        return Position(0.f, 0.f);
        break;
    case 1:
        return Position(m_size.x(), 0.f);
        break;
    case 2:
        return Position(m_size.x(), m_size.y());
        break;
    case 3:
        return Position(0.f, m_size.y());
        break;
    default:
        return Position(0.f, 0.f);
    }

    return Position(0.f, 0.f);
}

RectangleGeometry::OnUpdateSignal& RectangleGeometry::onUpdate()
{
    return m_onUpdate;
}

void RectangleGeometry::resize(const Position& size)
{
    m_size = size;
    m_onUpdate.emit();
}

const Position& RectangleGeometry::size() const
{
    return m_size;
}
