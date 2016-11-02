
// self
#include "CircleGeometry.h"

CircleGeometry::CircleGeometry(float radius, std::size_t resolution)
: Geometry()
, mRadius(radius)
, mResolution(resolution) {
  //
}

Geometry::size_type CircleGeometry::points() const {
  return mResolution;
}

Position CircleGeometry::pointAt(size_type index) const {
  return Position(0, 0);
}







