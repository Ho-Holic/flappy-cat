
// engine
#include "TriangleGeometry.hpp"

TriangleGeometry::TriangleGeometry(const Position& size)
    : Geometry()
    , m_size(size)
    , m_onUpdate()
{
    //
}

TriangleGeometry::TriangleGeometry()
    : TriangleGeometry(Position())
{
    //
}

TriangleGeometry::OnUpdateSignal& TriangleGeometry::onUpdate()
{
    return m_onUpdate;
}

void TriangleGeometry::resize(const Position& size)
{
    m_size = size;
    m_onUpdate.emit();
}

const Position& TriangleGeometry::size() const
{

    return m_size;
}

Geometry::size_type TriangleGeometry::points() const
{

    return 3;
}

Position TriangleGeometry::pointAt(Geometry::size_type index) const
{

    switch (index) {
    case 0:
        return Position(0.f, 0.f);
        break;
    case 1:
        return Position(m_size.x(), 0.f);
        break;
    case 2:
        return Position(0.f, m_size.y());
        break;
    default:
        return Position(0.f, 0.f);
    }

    return Position(0.f, 0.f);
}
