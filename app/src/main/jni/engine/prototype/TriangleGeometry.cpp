
// engine
#include "TriangleGeometry.hpp"

TriangleGeometry::TriangleGeometry(const Position& size)
    : Geometry()
    , mSize(size)
    , mOnUpdate()
{
    //
}

TriangleGeometry::OnUpdateSignal& TriangleGeometry::onUpdate()
{
    return mOnUpdate;
}

void TriangleGeometry::resize(const Position& size)
{
    mSize = size;
    mOnUpdate.emit();
}

const Position& TriangleGeometry::size() const
{

    return mSize;
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
        return Position(mSize.x(), 0.f);
        break;
    case 2:
        return Position(0.f, mSize.y());
        break;
    default:
        return Position(0.f, 0.f);
    }

    return Position(0.f, 0.f);
}
